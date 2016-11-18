#include"WaterRipple.h"
#include<cstring>
#include <assert.h>

WaterRipple::WaterRipple(int* pixels, int width,int height,int pixelFormat){
	Init(pixels,width,height,pixelFormat);
	this->m_fScale = 1;
}

WaterRipple::WaterRipple(int* pixels, int width, int height, int pixelFormat, float scale){
	Init(pixels, width, height, pixelFormat);
	this->m_fScale = scale;
}

void WaterRipple::Init(int* pixels, int width, int height, int pixelFormat){
	this->m_pOldPixels = new int[width*height];
	memcpy(m_pOldPixels, pixels, width*height*4);
	this->m_nWidth = width;
	this->m_nHeight = height;
	this->m_nPixelFormat = pixelFormat;
	this->m_nLength = width*height;

	this->m_pNewPixels = new int[m_nLength]{};

	memcpy(m_pNewPixels, pixels, m_nLength*sizeof(int));

	m_pBuf1 = new short[m_nLength]{};
	m_pBuf2 = new short[m_nLength]{};

	this->m_nPowerRate = 3;
}

WaterRipple::~WaterRipple(){
	if (!this->m_pBuf1){delete[] m_pBuf1;}
	if (!this->m_pBuf2){delete[] m_pBuf2;}
	if (!this->m_pOldPixels){ delete[] m_pNewPixels; }
	if (!this->m_pNewPixels){delete[] m_pNewPixels;}
	if (!this->m_pSourcePower){delete[] m_pSourcePower;}
	if (!this->m_nSourcePosition){delete[] m_nSourcePosition;}
}

void WaterRipple::SetWaveSource(int x, int y, int radius, int depth)
{
	SetWaveSourcePower(radius, depth);
	SetWaveSourcePosition(x, y);
}

//int WaterRipple::getPowerRate(){
//	return this->m_nPowerRate;
//}
//
//void WaterRipple::setPowerRate(int rate){
//	this->m_nPowerRate = rate;
//}
//
int* WaterRipple::NewPixels()
{
	return this->m_pNewPixels;
}
//
//int* WaterRipple::getOldPixels()
//{
//	return this->m_pOldPixels;
//}
//
//int WaterRipple::getWidth(){
//	return this->m_nWidth;
//}
//
//int WaterRipple::getHeight(){
//	return this->m_nHeight;
//}
//
//int WaterRipple::getLength(){
//	return this->m_nLength;
//}
//
//int WaterRipple::getPixelFormat(){
//	return this->m_nPixelFormat;
//}

inline
void WaterRipple::SetWaveSourcePower(int radius, int depth){

	this->m_nSourceRadius = static_cast<int>(radius/m_fScale);
	this->m_nSourceDepth = depth;

	InitSourcePower();
}

void WaterRipple::InitSourcePower(){
	
	int value = m_nSourceRadius*m_nSourceRadius;
	int diameter = (m_nSourceRadius << 1)+1;
	int rate = m_nSourceRadius/value ;	//波源能量分布

	int size = diameter*diameter;
	m_pSourcePower = new int[size]{};			//初始化波源能量为零
	m_nSourcePosition = new int[size]{};		//初始化波源位置为零

	for (int x = 0; x <= diameter; ++x){
		for (int y = 0; y <= diameter; ++y){
			int distanceSquare = (m_nSourceRadius - x)*(m_nSourceRadius - x) + (m_nSourceRadius - y)*(m_nSourceRadius - y);

			if (distanceSquare <= value){
				int depth = m_nSourceDepth - distanceSquare*rate;

				m_nSourcePosition[y*diameter + x] = y*m_nWidth + x;
				m_pSourcePower[y*diameter + x] = depth;
			}
		}
	}

}

inline
void WaterRipple::SetWaveSourcePosition(int x, int y){
	int sourceX = static_cast<int>(x/m_fScale);
	int sourceY = static_cast<int>(y / m_fScale);
	// 判断坐标是否在屏幕范围内
	if ((sourceX + m_nSourceRadius) >= m_nWidth || (sourceY + m_nSourceRadius) >= m_nHeight
		|| (sourceX - m_nSourceRadius) <= 0 || (sourceY - m_nSourceRadius) <= 0) {
		return;
	}


	//设置波源
	int distance = (sourceY - m_nSourceRadius)*m_nWidth + sourceX - m_nSourceRadius;
	int size = ((m_nSourceRadius << 1) + 1)* ((m_nSourceRadius << 1) + 1);
	for (int i = 0; i < size; ++i){
		m_pBuf1[distance + m_nSourcePosition[i]] = static_cast<short>(m_pSourcePower[i]);
	}
}

void WaterRipple::MoveLine(int startX, int startY, int endX, int endY){
	int dx = endX - startX;
	int dy = endY - startY;
	dx = (dx >= 0) ? dx : -dx;
	dy = (dy >= 0) ? dy : -dy;

	int currentX=startX;
	int currentY=startY;

	if (dx == 0 && dy == 0) {
		SetWaveSourcePosition(currentX, currentY);
	}
	else if (dx == 0) {
		int yinc = (endY - startY > 0) ? 1 : -1;
		for (int i = 0; i < dy; ++i) {
			SetWaveSourcePosition(currentX, currentY);
			currentY += yinc;
		}
	}
	else if (dy == 0) {
		int xinc = (endX - startX > 0) ? 1 : -1;
		for (int i = 0; i < dx; ++i) {
			SetWaveSourcePosition(currentX,currentY);
			currentX += xinc;
		}
	}
	else if (dx > dy) {
		int p = (dy << 1) - dx;
		int inc1 = (dy << 1);
		int inc2 = ((dy - dx) << 1);
		int xinc = (endX - startX > 0) ? 1 : -1;
		int yinc = (endY - startY > 0) ? 1 : -1;

		for (int i = 0; i < dx; ++i) {
			SetWaveSourcePosition(currentX, currentY);
			currentX += xinc;
			if (p < 0) {
				p += inc1;
			}
			else {
				currentY += yinc;
				p += inc2;
			}
		}
	}
	else if(dx>dy){
		int p = (dx << 1) - dy;
		int inc1 = (dx << 1);
		int inc2 = ((dx - dy) << 1);
		int xinc = (endX - startX > 0) ? 1 : -1;
		int yinc = (endY - startY > 0) ? 1 : -1;

		for (int i = 0; i < dy; ++i) {
			SetWaveSourcePosition(currentX, currentY);
			currentY += yinc;
			if (p < 0) {
				p += inc1;
			}
			else {
				startX += xinc;
				p += inc2;
			}
		}
	}
	else{
		int xinc = (endX - startX > 0) ? 1 : -1;
		int yinc = (endY - startY > 0) ? 1 : -1;

		for (int i = 0; i < dx; ++i){
			SetWaveSourcePosition(currentX, currentY);
			currentX += xinc;
			currentY += yinc;
		}
	}
}

inline
void WaterRipple::SpreedRipple(){

	int length = m_nWidth*(m_nHeight -1);
	for (int i = m_nWidth; i < length; ++i){
		m_pBuf2[i] = ((m_pBuf1[i - 1] + m_pBuf1[i - m_nWidth] + m_pBuf1[i + 1] + m_pBuf1[i + m_nWidth]) >> 1) - m_pBuf2[i];
		//波能衰减率
		m_pBuf2[i] -= m_pBuf2[i] >> m_nPowerRate;
	}
	short* temp = m_pBuf1;
	m_pBuf1 = m_pBuf2;
	m_pBuf2 = temp;
}

inline
void WaterRipple::RenderRipple(){

	int offset;
	int i = m_nWidth;
	for (int y = 1; y < m_nHeight - 1; ++y) {
		for (int x = 0; x < m_nWidth; ++x, ++i) {
			// 计算出偏移像素和原始像素的内存地址偏移量 :
			//offset = width * yoffset + xoffset
			offset = (m_nWidth * (m_pBuf1[i - m_nWidth] - m_pBuf1[i +
				m_nWidth])) + (m_pBuf1[i - 1] - m_pBuf1[i + 1]);
			// 判断坐标是否在范围内
			if (i + offset > 0 && i + offset < m_nLength) {
				m_pNewPixels[i] = m_pOldPixels[i + offset];
			}
			else {
				m_pNewPixels[i] = m_pOldPixels[i];
			}
		}
	}
}

void WaterRipple::Run(){
	SpreedRipple();
	RenderRipple();
}

//inline
//void WaterRipple::setPointPower(int x, int y, int depth){
//	int sourceX = x / m_fScale;
//	int sourceY = y / m_fScale;
//
//	m_pBuf1[y*m_nWidth + x] = depth;
//}
