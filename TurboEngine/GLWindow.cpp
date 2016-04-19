

void GlWindow::KeyDown(WPARAM wParam)
{
	keyPressed[wParam] = true;
	if (wParam == VK_F1 && actualLightning)
		actualLightning->NextType();
	if (wParam == VK_F3)
		NextCamera();
	if (wParam == VK_F4)
		actualCamera->fov += 1;
	if (wParam == VK_F5)
		actualCamera->fov -= 1;
	if (wParam == VK_F2)
	{

		if (!raceStarted)
			StartRace();
		else
			StopRace();
	}
}

//Main Loop
WPARAM GlWindow::Run()
{
	MSG msg;
	long time = GetTickCount();
	long elapsed = 0;
	while (shouldRun)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} //system messages handling
		KeyControl(elapsed / 1000.0f);
		UpdateObjects(elapsed);

		Animate(elapsed);
		DrawScene();
		// robienie rzeczy.

		long actualTime = GetTickCount();
		elapsed = actualTime - time;
		time = actualTime;
		if (elapsed < 30.0L)
			Sleep(30.0L - elapsed);

	}
	return msg.wParam;
}
float carSpeed = 3.0f;
void GlWindow::KeyControl(float time)
{
	if (cameraIndex == 0)
	{
		if (keyPressed['A'])//A
		{
			actualCamera->MoveByLocalVector(glm::vec3(10, 0, 0)*time);
		}
		if (keyPressed['S'])
		{
			actualCamera->MoveByLocalVector(glm::vec3(0, 0, -10)*time);
		}
		if (keyPressed['D'])//D
		{
			actualCamera->MoveByLocalVector(glm::vec3(-10, 0, 0)*time);
		}
		if (keyPressed['W'])
		{
			actualCamera->MoveByLocalVector(glm::vec3(0, 0, 10)*time);
		}
		if (keyPressed[VK_SHIFT])
		{
			actualCamera->MoveByLocalVector(glm::vec3(0, -10, 0)*time);
		}
		if (keyPressed[VK_SPACE])
		{
			actualCamera->MoveByLocalVector(glm::vec3(0, 10, 0)*time);
		}
	}
	else
	{
		if (keyPressed['A'])//A
		{
			userCar->Rotate(90.0f * time, 0, 0);
		}
		if (keyPressed['S'])
		{
			userCar->MoveByLocalVector(glm::vec3(0, 0, -10)*carSpeed*time);
		}
		if (keyPressed['D'])//D
		{
			userCar->Rotate(-90.0f * time, 0,0);
		}
		if (keyPressed['W'])
		{
			userCar->MoveByLocalVector(glm::vec3(0, 0, 10)*carSpeed*time);
		}
	}
	temp = NULL;
}

void GlWindow::MouseMoved(LPARAM lParam, WPARAM wParam)
{
	POINT mousePos{ LOWORD(lParam),HIWORD(lParam) };
	if (prevMousePos.x == -1)
		prevMousePos = mousePos;
	POINT move;
	move.x = mousePos.x - prevMousePos.x;
	move.y = mousePos.y - prevMousePos.y;
	float movement = (float)sqrt(move.x*move.x + move.y*move.y);
	if (movement > 3.0f)
	{
		if (cameraIndex != 1)
		{
			float wsp = 0.1f;
			float dx = move.x*wsp;
			float dy = move.y*wsp*2.0f;
			if (wParam & MK_LBUTTON)
			{
				actualCamera->Rotate(dx, dy,0);
			}
		}
		prevMousePos = mousePos;
	}
}

void GlWindow::LoadModels()
{
	Renderable* temp;
	Model* model = new Model("Nissan.3DS");
	std::vector<Renderable*> models;
	std::vector<std::vector<glm::vec3>> paths = makePaths();
	int i = 1;
	for (auto path : paths)
	{
		temp = new Renderable(model);
		temp->SetLocalPosition(glm::vec3(i*6.0f, 0, 0));
		temp->SetScale(glm::vec3(0.01f));
		temp->color = colors[i % 3];
		//parent->SetLocalRotationEuler(-glm::vec3(glm::pi<float>() / 2, 0, 0));
		temp->SetAnimation(new CurveAnimation(path, 20.0f));
		objRend->AddRenderable(temp);
		cars.push_back(temp);
		i++;
	}
	temp = new Renderable(model);
	temp->SetLocalPosition(glm::vec3(0, 0, 0));
	temp->SetScale(glm::vec3(0.01f));
	temp->color = glm::vec3(1.0f);
	objRend->AddRenderable(temp);
	cameras[2]->SetParent(temp);
	cameras[2]->SetLocalPosition(glm::vec3(0,2,-3));
	cameras[3]->WatchComponent(temp);
	userCar = temp;
	LoadBackground("Palm2.3DS");
	//parent = new Renderable(model);

}

void GlWindow::LoadBackground(char* objPath)
{
	Model* model = new Model(objPath);
	//D3Component* obj = new D3Component();
	//obj->SetLocalPosition(glm::vec3(0, 0, 0));s
	Renderable* tab[10];
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
		tab[i] = new Renderable(model);
		tab[i]->SetLocalPosition(glm::vec3(24, 0, 15+i*15));
		tab[i]->SetScale(glm::vec3((rand()%10+10) / 100.0));
		tab[i]->SetRotation(glm::quat(glm::vec3(glm::radians(-90.0f), 0, 0)));
		objRend->AddRenderable(tab[i]);
	}
	//tab[0]->SetLocalPosition(glm::vec3(10, 0, 0));


	//background;

	std::vector<Vertex>* vecs=new std::vector<Vertex>();
	std::vector<GLuint>* indices = new std::vector<GLuint>();
	vecs->push_back(Vertex(-20, 0, -20, 0, 1, 0, 1, 0));
	vecs->push_back(Vertex(-20, 0, 120, 0, 1, 0, 1, 0));
	vecs->push_back(Vertex(100, 0, 120, 0, 1, 0, 1, 0));
	vecs->push_back(Vertex(100, 0, -20, 0, 1, 0, 1, 0));
	indices->push_back(0);
	indices->push_back(1);
	indices->push_back(2);
	indices->push_back(0);
	indices->push_back(2);
	indices->push_back(3);
	Mesh* mesh= new Mesh(*vecs, *indices);
	Model* mod = new Model(mesh);
	Renderable* rend = new Renderable(mod);
	rend->color = glm::vec3(0.2f, 0.2f, 0.2f);
	objRend->AddRenderable(rend);
	//path
	std::vector<Vertex>* vecsP = new std::vector<Vertex>();
	std::vector<GLuint>* indicesP = new std::vector<GLuint>();
	vecsP->push_back(Vertex(0, 0.02f, -10.0f, 0, 1, 0, 1, 0));
	vecsP->push_back(Vertex(0, 0.02f, 110, 0, 1, 0, 1, 0));
	vecsP->push_back(Vertex(50, 0.02f, 110, 0, 1, 0, 1, 0));
	vecsP->push_back(Vertex(50, 0.02f, -10.0f, 0, 1, 0, 1, 0));
	vecsP->push_back(Vertex(25, 0.02f, 10, 0, 1, 0, 1, 0));
	vecsP->push_back(Vertex(25, 0.02f, 90, 0, 1, 0, 1, 0));
	vecsP->push_back(Vertex(35, 0.02f, 90, 0, 1, 0, 1, 0));
	vecsP->push_back(Vertex(35, 0.02f, 10, 0, 1, 0, 1, 0));
	indicesP->push_back(0);
	indicesP->push_back(1);
	indicesP->push_back(4);
	indicesP->push_back(4);
	indicesP->push_back(1);
	indicesP->push_back(5);

	indicesP->push_back(1);
	indicesP->push_back(2);
	indicesP->push_back(5);
	indicesP->push_back(5);
	indicesP->push_back(2);
	indicesP->push_back(6);

	indicesP->push_back(2);
	indicesP->push_back(3);
	indicesP->push_back(6);
	indicesP->push_back(6);
	indicesP->push_back(3);
	indicesP->push_back(7);

	indicesP->push_back(3);
	indicesP->push_back(0);
	indicesP->push_back(7);
	indicesP->push_back(7);
	indicesP->push_back(0);
	indicesP->push_back(4);
	Mesh* meshP = new Mesh(*vecsP, *indicesP);
	Model* modP = new Model(meshP);
	rend = new Renderable(modP);
	rend->SetLocalPosition(glm::vec3(-5.0f, 0, 0));
	rend->color = glm::vec3(0.4f, 0.2f, 0.2f);
	objRend->AddRenderable(rend);
	//path


}


void GlWindow::SetScene()
{
	ShaderProgram* shader = new ShaderProgram("BasicVertex.vsh", "BasicFragment.fsh");
	if (shader->programId == 0)
		exit(EXIT_FAILURE);
	objRend = new ObjectRenderer(windowWidth, windowHeight, shader);
	cameras.push_back(new Camera(glm::vec3(0, 2, -4), glm::quat(glm::vec3(0, 0, 0)), glm::vec3(0, 1, 0), 1.0f, 200.0f, 60));
	cameras.push_back(new Camera(glm::vec3(0, 55, 50), glm::quat(glm::vec3(glm::radians(65.0f), glm::radians(90.0f), 0)), glm::vec3(0, 1, 0), 1.0f, 200.0f, 80));
	cameras.push_back(new Camera(glm::vec3(20, 65, 50), glm::quat(glm::vec3(0, 0, 0)), glm::vec3(0, 1, 0), 1.0f, 200.0f, 60));
	cameras.push_back(new Camera(glm::vec3(0, 25, 50), glm::quat(glm::vec3(0, 0, 0)), glm::vec3(0, 1, 0), 1.0f, 200.0f, 60));
	
	cameraIndex = 0;
	actualCamera = cameras[0];
	LoadModels();
	actualLightning = new Scene(glm::vec3(0, 3, 3), glm::vec3(1, 1, 1), 0);
}
