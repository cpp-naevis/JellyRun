#pragma once
#include <afxwin.h>

class CLevel
{
private:
    CPoint pos;           // ��ġ
    int speed;            // �̵� �ӵ�
    bool appeared;        // ��� ���� ����
    bool levelUp;         // ������ ����
    CRect rect;           // �浹 ���� ����
    CBitmap bmp;          // ��Ʈ��
    bool bmpLoaded;       // ��Ʈ�� �ε� Ȯ��
    

public:
    CLevel();
    ~CLevel();

    void Init();                     // �ʱ�ȭ
    void Update(int elapsedTime);    // �ð��� ���� ������Ʈ
    void Draw(CDC* pDC);             // ȭ�鿡 �׸�
    void CheckCollision(CRect playerRect); // �浹 Ȯ��
    bool IsAppeared() const;
    bool IsLevelUp() const;
    CPoint GetPosition() const;
};

