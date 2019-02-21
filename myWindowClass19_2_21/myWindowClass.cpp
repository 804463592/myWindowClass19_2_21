#include <windows.h>

// ����ע��Ĵ�������
const char g_szClassName[] = "myWindowClass";

void myPaint(HWND hwnd)
{
	// paint struct ��ͼ�ṹ�壬�洢Ŀ�괰�ڿ��Ի�ͼ�Ŀͻ�������(client area)
	PAINTSTRUCT ps;
	HDC hdc;   // DC(�ɻ�ͼ���ڴ����) �ľ��
	HPEN hpen; // ����

	// ͨ�����ھ����ȡ�ô��ڵ� DC
	hdc = BeginPaint(hwnd, &ps);
	// ��������
	hpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	// DC ѡ�񻭱�
	SelectObject(hdc, hpen);
	// (����)�ӳ�ʼ���ƶ��� 50,50
	MoveToEx(hdc, 50, 50, NULL);
	// (����)�ӳ�ʼ�㻭�ߵ� 100,100
	LineTo(hdc, 150, 100);
	MoveToEx(hdc, 150, 100, NULL);
	LineTo(hdc, 40, 400);

	EndPaint(hwnd, &ps);//BeginPaint �� EndPaint�����ڴ�Ŀ�괰�ڻ�ȡ�ɻ�ͼ�� DC���Լ��ر���� DC
}

/*
���ƽ���ɫ
*/

void gradientPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc;   // DC(�ɻ�ͼ���ڴ����) �ľ��
	HPEN hpen; // ����
	int red, blue; // �졢����ɫ
	int y = 1, x = 1; // �С���

	// ͨ�����ھ����ȡ�ô��ڵ� DC
	hdc = BeginPaint(hwnd, &ps);

	for (red = 0; red < 256; red++)
	{
		for (blue = 0; blue < 256; blue++)
		{
			/*
	        //��������
				PS_SOLID,       //   ֱ��
				PS_DASH,        // -------
				PS_DOT,         // .......
				PS_DASHDOT,     // _._._._
				PS_DASHDOTDOT,  // _.._.._
				PS_NULL         //
	        */
	        // ��������
			hpen = CreatePen(PS_SOLID, 1, RGB(red, 0, blue));
			// ѡ�л���
			SelectObject(hdc, hpen);

			// ��һ���� (x, y) �� (x, y+1) �Ĵ�ֱ����
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x++, y + 1);

			// ɾ������
			DeleteObject(hpen);
		}
		// һ�л��� ��+1, �������� 1
		y += 1;
		x = 1;
	}

	// �ر�DC ��������
	EndPaint(hwnd, &ps);
}


/*
 * ѡ������
 */
HFONT ChooseMyFont()
{
	CHOOSEFONT cf;
	LOGFONT lf;
	HFONT hfont;

	// CHOOSEFONT �ṹ 
	cf.lStructSize = sizeof(CHOOSEFONT);
	cf.hwndOwner = (HWND)NULL;
	cf.hDC = (HDC)NULL;
	cf.lpLogFont = &lf;
	cf.iPointSize = 0;
	cf.Flags = CF_SCREENFONTS;
	cf.rgbColors = RGB(0, 0, 0);
	cf.lCustData = 0L;
	cf.lpfnHook = (LPCFHOOKPROC)NULL;
	cf.lpTemplateName = (LPSTR)NULL;
	cf.hInstance = (HINSTANCE)NULL;
	cf.lpszStyle = (LPSTR)NULL;
	cf.nFontType = SCREEN_FONTTYPE;
	cf.nSizeMin = 0;
	cf.nSizeMax = 0;

	// ѡ������Ի��� 
	ChooseFont(&cf);
	// �õ�HFONT ����
	hfont = CreateFontIndirect(cf.lpLogFont);
	return (hfont);
}

void fontPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HFONT hFontSetting;

	hdc = BeginPaint(hwnd, &ps);

	// ������������
	hFontSetting = ChooseMyFont();
	// DC ��������
	SelectObject(hdc, hFontSetting);

	// ͬ��������� Helloworld
	TextOut(hdc, 0, 0, TEXT("Hello world"), sizeof(TEXT("Hello world")));

	EndPaint(hwnd, &ps);
}




/*
 * ���Ĳ�,���ڹ���
 */
LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// ���ڻ�����Ϣ
	case WM_PAINT:
		/*
		 * ����ֻ��Ҫ������������ǵ� GDI ���ƺ����Ϳ��ԣ������ط�����������
		 * ������ִ�е�����ط���ʱ����ζ��ϵͳ�����ǵĳ������� WM_PAINT ��Ϣ
		 * Ҳ���Ǹ������ǵĳ��򣬿��Կ�ʼ���ƴ��ڵ������ˡ�
		 */
		 //PS��Ĭ������£�ϵͳֻ�������ǵĳ�����һ�� WM_PAINT ��Ϣ��
		 //�����Ҫ����һ�Σ���Ҫʹ�� SendMessage ���������Լ����Լ��ֶ����͸���Ϣ��

		 //myPaint(hwnd); // �������ǵ� GDI ���ƺ���
		//gradientPaint(hwnd);
		fontPaint(hwnd); // �������ǵ� GDI ���ƺ���


		break;
		// ���ڹر���Ϣ
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
		// ����������Ϣ
	case WM_DESTROY:
		PostQuitMessage(0); // �����뿪��Ϣ��ϵͳ
		break;
		// ������Ϣ
	default:
		// pass ��ϵͳ���۲���
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

/*
 * ��һ��,ע�ᴰ����
 */
void RegisterMyWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wc;

	// 1)���ô�������
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = MyWindowProc; // ���õ��Ĳ��Ĵ��ڹ��̻ص�����
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// 2)ע��
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("����ע��ʧ��!"), TEXT("����"), MB_ICONEXCLAMATION | MB_OK);
		exit(0); // �����˳�
	}
}

/*
 * �ڶ�������������
 */
HWND CreateMyWindow(HINSTANCE hInstance, int nCmdShow)
{
	HWND hwnd;
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		TEXT("�ҵĴ�������"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, // �������� x,y Ĭ�Ϸ��� ���ڿ� 400 �� 300
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, TEXT("���ڴ���ʧ��!"), TEXT("����"), MB_ICONEXCLAMATION | MB_OK);
		exit(0); // �����˳�
	}

	// ��ʾ����
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	return hwnd;
}

/*
 * ������
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG Msg;

	// ��һ��,ע�ᴰ����
	RegisterMyWindow(hInstance);
	// �ڶ���:��������
	hwnd = CreateMyWindow(hInstance, nCmdShow);
	// ������:��Ϣѭ��
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}