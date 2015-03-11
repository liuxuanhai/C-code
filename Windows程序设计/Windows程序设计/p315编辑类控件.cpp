#define	SZAPPNAME	"p315编辑类控件"
#define ID_EDIT		1
#include			"DX_WinMain.cpp"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndEdit;

	switch (message)
	{
	case WM_CREATE:
		hwndEdit = CreateWindow(TEXT("edit"), NULL, 
			WS_CHILD | WS_VISIBLE | 
			WS_HSCROLL | WS_VSCROLL | // 增加编辑控件滚动条
			WS_BORDER | // 默认情况下, 一个编辑控件 是没有边框的, 可以这样添加边框
			ES_LEFT | // 编辑控件中的文本样式
			ES_MULTILINE | // 默认情况下, 一个编辑控件只有一行, 可以用ES_MULTILINE创建一个多行编辑空间
			ES_AUTOHSCROLL |  // 创建一个可以自动水平滚动的编辑控件 
			ES_AUTOVSCROLL,
			0, 0, 0, 0, hwnd, (HMENU)ID_EDIT,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);
		return 0;

	case WM_SETFOCUS:
		SetFocus(hwndEdit);
		return 0;

	case WM_SIZE:
		MoveWindow(hwndEdit, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		return 0;

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_EDIT)
			if (HIWORD(wParam) == EN_ERRSPACE ||  // 编辑控件没有空间了
				HIWORD(wParam) == EN_MAXTEXT)  // 编辑控件没有空间完成插入了
				MessageBox(hwnd, TEXT("文本控件站不下这么多文字"), TEXT(SZAPPNAME), MB_OK | MB_ICONSTOP);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}