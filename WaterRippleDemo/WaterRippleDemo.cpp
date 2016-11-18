#include "WaterRippleDemo.h"
#include "QImage"
#include "QLabel"
#include "QPixmap"
#include "WaterRipple.h"
#include <thread>
#include <future>

WaterRippleDemo::WaterRippleDemo(QWidget *parent)
	: QWidget(parent)
	, m_image(new QImage(":/WaterRippleDemo/Resources/water.jpg"))
{
	m_waterRipple.reset(new WaterRipple((int*)(m_image->bits()),m_image->size().width(),m_image->size().height(),m_image->format()));
	m_label = new QLabel(this);
	m_label->setPixmap(QPixmap::fromImage(*m_image));

	setFixedSize(m_image->size());

	StartRun();
}

WaterRippleDemo::~WaterRippleDemo()
{
	StopRun();
}

void WaterRippleDemo::StartRun()
{
	m_admitRun = true;

	m_waterRipple->SetWaveSource(m_image->size().width() / 2, m_image->size().height() / 2, 10, 100);

	m_future=std::async(std::launch::async,&WaterRippleDemo::Run,this);
}

void WaterRippleDemo::StopRun()
{
	m_admitRun = false;
	m_future.get();
}

void WaterRippleDemo::Run()
{
	while (m_admitRun)
	{
		m_waterRipple->Run();
		memcpy(m_image->bits(), (const uchar*)m_waterRipple->NewPixels(), m_image->byteCount());
		m_label->setPixmap(QPixmap::fromImage(*m_image));
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
