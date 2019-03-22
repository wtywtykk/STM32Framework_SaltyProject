#pragma once

#include "Kernel\Common\KCommon.h"
#include "User\BodePlotterDataStore.h"
#include "Kernel\GUI\DC\DC.h"

class BodePlotterGraphic
{
private:
	const GUIPOS DivCountX = 10;
	const GUIPOS PixelsPerDivX = 70;
	const GUIPOS DivCountY = 8;
	const GUIPOS PixelsPerDivY = 48;
	const GUIPOS Width = DivCountX * PixelsPerDivX;
	const GUIPOS Height = DivCountY * PixelsPerDivY;
	const PIXEL Color = YELLOW;
	const PIXEL UpdateColor = RED;

	double Start = 0.0;
	double End = 1.0;
	bool LogScan = false;
	double Base = 0.0;
	double PerDiv = 0.1;
	bool LogAmpt = false;

	DC* DrawingDC = NULL;

public:
	~BodePlotterGraphic(void);
	void AssignDC(DC* dc);
	void SetFreqParam(double StartFreq, double EndFreq, bool LogScanType);
	void SetAmptParam(double BaseAmpt, double AmptPerDiv, bool LogAmptType);
	void Draw(BodePlotterDataStore* LastFull, BodePlotterDataStore* CurrentData);

private:
	void DrawGrid(void);
	GUIPOS FreqToCoord(double Freq);
	GUIPOS AmptToCoord(double Ampt);
	void DrawDataStore(BodePlotterDataStore* DataStore, double StartFreq, double EndFreq);
};
