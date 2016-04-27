﻿#pragma once
#include "TurboEngine.h"

class Module
{
protected:
	TurboEngine* engine;
public:
	void virtual Update(float time) abstract;
	void virtual Initialize(TurboEngine* engine);
	void virtual EndWork() abstract;
};