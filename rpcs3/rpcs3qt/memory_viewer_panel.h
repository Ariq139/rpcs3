#pragma once

#include "util/types.hpp"

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QFont>
#include <QFontDatabase>

#include <string>

class cpu_thread;

namespace utils
{
	class shm;
}

class memory_viewer_panel : public QDialog
{
	Q_OBJECT

public:
	memory_viewer_panel(QWidget* parent, u32 addr = 0, const std::shared_ptr<cpu_thread>& cpu = nullptr);
	~memory_viewer_panel();

	enum class color_format : int
	{
		RGB,
		ARGB,
		RGBA,
		ABGR
	};
	Q_ENUM(color_format)

protected:
	void wheelEvent(QWheelEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

private:
	u32 m_addr;
	u32 m_colcount;
	u32 m_rowcount;

	QLineEdit* m_addr_line;

	QLabel* m_mem_addr;
	QLabel* m_mem_hex;
	QLabel* m_mem_ascii;

	QFontMetrics* m_fontMetrics;

	enum class thread_type
	{
		ppu,
		spu,
		//rsx
	};

	const thread_type m_type;
	const std::shared_ptr<utils::shm> m_spu_shm;
	const u32 m_addr_mask;

	std::string getHeaderAtAddr(u32 addr);
	void scroll(s32 steps);
	void SetPC(const uint pc);

	virtual void ShowMemory();

	void ShowImage(QWidget* parent, u32 addr, color_format format, u32 sizex, u32 sizey, bool flipv);
};
