
#include "GUIEditor.h"
#include "PublicHeaders.h"
#include "KudFileHelper.h"

using namespace KUDEET;
using namespace GUI;
using namespace LAYOUT;

IGUIManager * g_pMgr = NULL;

class IEventHandlerImpl22 : public IEventHandler
{
public:

	KDE_BEGIN_MSG_MAP(IEventHandlerImpl22)
		KDE_GUI_MSG_HANDLER(KGE_BUTTON_CLICKED, OnButtonClicked)
	KDE_END_MSG_MAP()

	bool OnButtonClicked(const KDS_EVENT& event)
	{
		return true;
	}
};

class IEventHandlerImpl : public IEventHandler
{
public:

	KDE_BEGIN_MSG_MAP(IEventHandlerImpl)
		KDE_GUI_MSG_HANDLER(KGE_BUTTON_CLICKED, OnButtonClicked)
	KDE_END_MSG_MAP()

	bool OnButtonClicked(const KDS_EVENT& event)
	{
		IGUIWindow * pWnd = g_pMgr->GetLayoutWindow(L"mainWindow");
		IGUIWindow * pWnd2 = g_pMgr->GetLayoutWindow(L"mainWindow2");
		if (pWnd != NULL)
		{
			pWnd->SetOwner(pWnd2);
			pWnd->ShowModal();
		}
		return true;
	}
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	g_pMgr = CreateGUIManager();
	IEventHandlerImpl impl;
	if (g_pMgr != NULL)
	{
		{
			TCHAR szPath[256] = {0};
			KFileSystemHelper::GetModulePath(NULL, szPath);
			KString strFolder = szPath;
			strFolder.append(L"\\Skins");
			KString strLayout = strFolder.append(L"\\MainLayout.xml");

			g_pMgr->LoadLayout(strLayout);
			IGUIWindow * pWnd = g_pMgr->GetLayoutWindow(L"mainWindow2");
			if (NULL == pWnd)
				return 0;

			pWnd->SetEventHandler(&impl);
			pWnd->CenterWindow();

			////////
            
			/*IGUIElement * pBtn = pWnd->CreateElement(EET_CONTROL_BUTTON, KRect(20, 20, 120, 50));
			
			pBtn->SetElementText(L"Button");

			IGUIElement * pLabel = pWnd->CreateElement(EET_CONTROL_LABEL, KRect(60, 60, 180, 180));
			pLabel->SetElementText(L"Hello Label");*/

			pWnd->ShowWindow(SW_SHOW);
			
			SInt32 nRet = pWnd->Run();

			return nRet;
		}
	}

	DestroyGUIManager(g_pMgr);

	return 0;
}

