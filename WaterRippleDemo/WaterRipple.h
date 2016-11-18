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


	void SetWaveSource(int x, int y, int radius, int depth);	/*���ò�Դ*/
	void MoveLine(int startX,int startY,int endX,int endY);

	void Run();			//��ʼ��Ⱦ


private:
	void SetWaveSourcePower(int radius, int depth);		//���ò�Դ��С
	////void setPointPower(int x, int y, int depth);		//������һ�㲨Դ��С
	void SetWaveSourcePosition(int x, int y);	//���ò�Դ

	void SpreedRipple();		//ˮ����ɢ
	void RenderRipple();		//ˮ����Ⱦ
	void Init(int* pixels, int width, int height, int pixelFormat);	//��ʼ��
	void InitSourcePower();	//��(0,0)��Ϊ���������Ͻǣ���ʼ����Դ��С 

private:
	int* m_pOldPixels=nullptr;	//ԭʼ���ص�
	int* m_pNewPixels=nullptr; //��Ⱦ������ص�
	short* m_pBuf1 = nullptr;		//���ܻ�����1
	short* m_pBuf2 = nullptr;		//���ܻ�����2
	int* m_pSourcePower = nullptr;	//��Դ����
	int* m_nSourcePosition = nullptr;	//��Դλ��

	int m_nWidth;		//ͼƬ��ȣ����أ�
	int m_nHeight;	//ͼƬ�߶�
	int m_nLength;	//���ص�����
	int m_nPixelFormat;	//ͼƬ��ʽ

	int m_nPowerRate;	//����˥����(power-=power>>m_powerRater)

	float m_fScale;	//ͼƬ��������

	int m_nSourceRadius;	//��Դ�뾶
	int m_nSourceDepth;	//��Դ���
};

#endif