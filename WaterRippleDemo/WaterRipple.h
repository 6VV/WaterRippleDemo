#ifndef _WAVE_H
#define _WAVE_H

class WaterRipple
{
public:
	//void setPixels(int*);
	//void setWidth(int);
	//void setHeight(int);
	//void setPixelFormat(int);
	//void setPowerRate(int rate);

	int* NewPixels();
	//int* getOldPixels();
	//int getWidth();
	//int getHeight();
	//int getLength();
	//int getPowerRate();
	//int getPixelFormat();

	WaterRipple(int* pixels,int width,int height,int pixelFormat);
	WaterRipple(int* pixels, int width, int height, int pixelFormat,float scale);
	~WaterRipple();


	void SetWaveSource(int x, int y, int radius, int depth);	/*设置波源*/
	void MoveLine(int startX,int startY,int endX,int endY);

	void Run();			//开始渲染


private:
	void SetWaveSourcePower(int radius, int depth);		//设置波源大小
	////void setPointPower(int x, int y, int depth);		//设置任一点波源大小
	void SetWaveSourcePosition(int x, int y);	//设置波源

	void SpreedRipple();		//水波扩散
	void RenderRipple();		//水波渲染
	void Init(int* pixels, int width, int height, int pixelFormat);	//初始化
	void InitSourcePower();	//以(0,0)点为正方形左上角，初始化波源大小 

private:
	int* m_pOldPixels=nullptr;	//原始像素点
	int* m_pNewPixels=nullptr; //渲染后的像素点
	short* m_pBuf1 = nullptr;		//波能缓冲区1
	short* m_pBuf2 = nullptr;		//波能缓冲区2
	int* m_pSourcePower = nullptr;	//波源数据
	int* m_nSourcePosition = nullptr;	//波源位置

	int m_nWidth;		//图片宽度（像素）
	int m_nHeight;	//图片高度
	int m_nLength;	//像素点总数
	int m_nPixelFormat;	//图片格式

	int m_nPowerRate;	//波能衰减率(power-=power>>m_powerRater)

	float m_fScale;	//图片伸缩比例

	int m_nSourceRadius;	//波源半径
	int m_nSourceDepth;	//波源深度
};

#endif