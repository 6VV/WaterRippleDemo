#ifndef WATERRIPPLEDEMO_H
#define WATERRIPPLEDEMO_H

#include <QWidget>
#include <memory>
#include <future>

class QImage;
class WaterRipple;
class QLabel;

class WaterRippleDemo : public QWidget
{
	Q_OBJECT

public:
	WaterRippleDemo(QWidget *parent = 0);
	~WaterRippleDemo();

	void StartRun();
	void StopRun();

private:
	void Run();

private:
	std::unique_ptr<QImage> m_image;
	std::unique_ptr<WaterRipple> m_waterRipple;
	QLabel* m_label;
	bool m_admitRun = false;
	std::future<void> m_future;
};

#endif // WATERRIPPLEDEMO_H
