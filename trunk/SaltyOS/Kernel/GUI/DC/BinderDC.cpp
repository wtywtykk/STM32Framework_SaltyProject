#include "Kernel\GUI\GUICommon.h"
#include "Kernel\Common\KObject.h"
#include "Kernel\GUI\DC\DC.h"
#include "BinderDC.h"
#include <assert.h>

BINDERDC::BINDERDC(DC * DC1, DC * DC2)
{
	assert(DC1);
	assert(DC2);
	m_DC1 = NewReferenceSafe(DC1);
	m_DC2 = NewReferenceSafe(DC2);
}

BINDERDC::~BINDERDC(void)
{
	FreeAndEraseReference(m_DC1);
	FreeAndEraseReference(m_DC2);
}

void BINDERDC::Fill(GUIPOS X1, GUIPOS Y1, GUIPOS X2, GUIPOS Y2, PIXEL Color)
{
	if (m_DC1)
	{
		m_DC1->Fill(X1, Y1, X2, Y2, Color);
	}
	if (m_DC2)
	{
		m_DC2->Fill(X1, Y1, X2, Y2, Color);
	}
}

void BINDERDC::SetPos(GUIPOS X, GUIPOS Y)
{
	if (m_DC1)
	{
		m_DC1->SetPos(X, Y);
	}
	if (m_DC2)
	{
		m_DC2->SetPos(X, Y);
	}
}

void BINDERDC::SequenceWrite(PIXEL Color)
{
	if (m_DC1)
	{
		m_DC1->SequenceWrite(Color);
	}
	if (m_DC2)
	{
		m_DC2->SequenceWrite(Color);
	}
}

void BINDERDC::SetPixel(GUIPOS X, GUIPOS Y, PIXEL Color)
{
	if (m_DC1)
	{
		m_DC1->SetPixel(X, Y, Color);
	}
	if (m_DC2)
	{
		m_DC2->SetPixel(X, Y, Color);
	}
}

PIXEL BINDERDC::GetPixel(GUIPOS X, GUIPOS Y)
{
	if (m_DC1)
	{
		return m_DC1->GetPixel(X, Y);
	}
	else
	{
		return 0;
	}
}

PIXEL BINDERDC::SequenceRead(void)
{
	if (m_DC1)
	{
		return m_DC1->SequenceRead();
	}
	else
	{
		return 0;
	}
}

GUIPOS BINDERDC::GetWidth(void)
{
	if (m_DC1)
	{
		return m_DC1->GetWidth();
	}
	else
	{
		return 0;
	}
}

GUIPOS BINDERDC::GetHeight(void)
{
	if (m_DC1)
	{
		return m_DC1->GetHeight();
	}
	else
	{
		return 0;
	}
}

bool BINDERDC::SupportNativeClip(void)
{
	if (m_DC1 && m_DC2)
	{
		return m_DC1->SupportNativeClip() && m_DC2->SupportNativeClip();
	}
	else
	{
		return false;
	}
}

void BINDERDC::StartNativeClip(GUIPOS X1, GUIPOS Y1, GUIPOS X2, GUIPOS Y2)
{
	if (m_DC1 && m_DC2)
	{
		m_DC1->StartNativeClip(X1, Y1, X2, Y2);
		m_DC2->StartNativeClip(X1, Y1, X2, Y2);
	}
}

void BINDERDC::EndNativeClip(void)
{
	if (m_DC1 && m_DC2)
	{
		m_DC1->EndNativeClip();
		m_DC2->EndNativeClip();
	}
}

void BINDERDC::BlockWrite(const PIXEL* Data, u32 Length)
{
	if (m_DC1)
	{
		m_DC1->BlockWrite(Data, Length);
	}
	if (m_DC2)
	{
		m_DC2->BlockWrite(Data, Length);
	}
}
