#include<math.h>
#include<cmath>
#include<stdlib.h>
#include<stdio.h>
#include<glut.h>

int directionForwardBackward = 0, directionRightLeft = 0;
int roverWheelRotation = 0, roverAltitude = 0;
int cameraDistance = 1, idleCounter = 0, isDisplayed = 0;
int boundaryX = 0, boundaryZ = 0, mapAltitudeStatus = 0;
int angleShoulder = 0, angleElbow = 0, angleWrist = 0, angleFinger = 0, angleRover = 0;
int stateShoulder = 0, stateElbow = 0, stateWrist = 0, stateFinger = 0;
float angleAntenna = 0, angleCamera = 0;
float cameraX = 0, cameraZ = 0;

void display() {

	glClear(GL_COLOR_BUFFER_BIT);

	int pointZ = 0; // z noktası
	int pointX = 20; // x noktası
	int pointY[] = {
		14, 25, 45, 55, 68, 70, 84, 91, 97, 101, 105, 105, 105, 105, 110, 110, 110, 110, 110, 110, 110,
		5, 18, 43, 62, 73, 82, 88, 94, 99, 102, 105, 105, 105, 105, 110, 110, 110, 110, 110, 110, 110,
		5, 18, 38, 56, 69, 77, 86, 94, 99, 103, 106, 105, 105, 105, 110, 110, 110, 110, 110, 110, 110,
		5, 9, 31, 48, 60, 71, 81, 87, 95, 101, 106, 105, 105, 105, 110, 110, 110, 110, 110, 110, 110,
		5, 5, 18, 37, 49, 56, 62, 81, 91, 94, 101, 105, 105, 105, 110, 110, 110, 110, 110, 110, 110,
		5, 5, 12, 23, 34, 40, 53, 66, 77, 82, 97, 103, 105, 105, 109, 110, 110, 110, 110, 115, 115,
		4, 5, 8, 15, 20, 24, 35, 39, 40, 77, 92, 101, 104, 104, 105, 110, 110, 110, 115, 115, 115,
		5, 7, 22, 36, 46, 48, 48, 44, 50, 58, 80, 96, 96, 97, 106, 110, 110, 115, 115, 115, 115,
		4, 15, 31, 46, 61, 68, 69, 63, 53, 50, 67, 82, 84, 103, 108, 110, 110, 115, 115, 115, 115,
		4, 12, 31, 46, 64, 78, 82, 80, 69, 54, 73, 71, 92, 105, 108, 110, 110, 115, 115, 115, 115,
		6, 26, 35, 45, 63, 75, 84, 87, 84, 74, 77, 80, 96, 103, 108, 110, 110, 110, 115, 115, 115,
		21, 30, 46, 57, 64, 76, 85, 92, 92, 87, 79, 80, 86, 102, 106, 110, 105, 110, 115, 115, 115,
		27, 40, 48, 62, 75, 84, 92, 96, 97, 94, 88, 80, 80, 91, 104, 105, 105, 105, 110, 115, 115,
		33, 43, 55, 65, 75, 87, 96, 101, 101, 101, 97, 92, 80, 80, 98, 105, 105, 105, 105, 110, 115,
		45, 50, 58, 68, 80, 91, 99, 102, 105, 105, 105, 99, 90, 80, 80, 97, 105, 105, 105, 110, 100,
		50, 60, 65, 71, 84, 95, 101, 105, 105, 107, 107, 106, 102, 101, 92, 80, 98, 104, 105, 100, 100,
		60, 70, 76, 83, 88, 96, 103, 106, 107, 108, 110, 109, 108, 108, 106, 101, 90, 100, 100, 100, 100 }; // y değerleri

	if (isDisplayed == 0) // Kamerayı ve harita ölçeklemeyi sadece 1 kere çağır
	{
		gluLookAt(45, 50, 40, 0, 0, -300, 0, 1, 0);
		glScalef(0.25, 0.25, 0.25);
		isDisplayed = 1;
	}

	for (int i = 0; i <= 334; i++)
	{
		float averageMapColor = (pointY[i] + pointY[i + 21] + pointY[i + 1]) / 3; // Her çizginin ortalama değeri bulunur
		float averageMapColor2 = (pointY[i + 22] + pointY[i + 21] + pointY[i + 1]) / 3; // Her çizginin ortalama değeri bulunur

		if (mapAltitudeStatus == 1) // 'H' tuşuna basıldığında haritanın rengini değiştiren algoritma
		{
			if (averageMapColor <= 50) // Noktaların ortalamaları <= 50 ise yeşil
			{
				glColor3f(0.0, 1.0, 0.0);
			}
			else if (averageMapColor <= 80 && averageMapColor > 50) // Noktaların ortalamaları <=80 ve >50 ise sarı
			{
				glColor3f(1.0, 1.0, 0.0);
			}
			else if (averageMapColor > 80) // Noktaların ortalamaları >80 ise kırmızı
			{
				glColor3f(1.0, 0.0, 0.0);
			}
		}
		else // 'H' tuşuna tekrar basıldığında renklendirmeyi devre dışı bırak
		{
			glColor3f(1.0, 1.0, 1.0);
		}

		glBegin(GL_LINE_LOOP); // Üçgen oluşturmak için gerekli algoritma 1
		glVertex3f(pointX - 20, pointY[i], pointZ);
		glVertex3f(pointX, pointY[i + 21], pointZ);
		glVertex3f(pointX - 20, pointY[i + 1], pointZ - 20);
		glEnd();

		if (mapAltitudeStatus == 1) // 'H' tuşuna basıldığında haritanın rengini değiştiren algoritma
		{
			if (averageMapColor2 <= 50) // Noktaların ortalamaları <= 50 ise yeşil
			{
				glColor3f(0.0, 1.0, 0.0);
			}
			else if (averageMapColor2 <= 80 && averageMapColor > 50) // Noktaların ortalamaları <=80 ve >50 ise sarı
			{
				glColor3f(1.0, 1.0, 0.0);
			}
			else if (averageMapColor2 > 80) // Noktaların ortalamaları >80 ise kırmızı
			{
				glColor3f(1.0, 0.0, 0.0);
			}
		}
		else // 'H' tuşuna tekrar basıldığında renklendirmeyi devre dışı bırak
		{
			glColor3f(1.0, 1.0, 1.0);
		}

		glBegin(GL_LINE_LOOP); // Üçgen oluşturmak için gerekli algoritma 2
		glVertex3f(pointX, pointY[i + 21], pointZ);
		glVertex3f(pointX - 20, pointY[i + 1], pointZ - 20);
		glVertex3f(pointX, pointY[i + 22], pointZ - 20);
		glEnd();
		pointZ -= 20;
		if ((i + 2) % 21 == 0 && i != 0) // Bir sütun boyunca noktalar basılır. En son x değeri sağa geçer, z sıfırlanır ve bir sonraki sütun oluşturulur.
		{
			pointX = pointX + 20;
			pointZ = 0;
			i++;
		}
	}
	glPushMatrix(); //-------------------------------------------- ROBOT BAŞLANGICI --------------------------------------------

	glTranslatef(directionRightLeft, pointY[roverAltitude] + 20, directionForwardBackward);
	glRotatef(angleRover, 0, 1, 0);

	//-------------------- TEKERLEK BAŞLANGICI --------------------
	// Tekerlek sol arka
	glPushMatrix();
	glColor3f(0, 1, 1);
	glTranslatef(-10, -5, -20);
	glRotatef(roverWheelRotation % 360, 0, 0, 1); // Robot hareket ettiğinde tekerlekler döner
	glutWireSphere(6, 6, 6);
	glPopMatrix();

	// Tekerlek sol ön
	glPushMatrix();
	glColor3f(0, 1, 1);
	glTranslatef(10, -5, -20);
	glRotatef(roverWheelRotation % 360, 0, 0, 1); // Robot hareket ettiğinde tekerlekler döner
	glutWireSphere(6, 6, 6);
	glPopMatrix();

	// Tekerlek sağ arka
	glPushMatrix();
	glColor3f(0, 1, 1);
	glTranslatef(-10, -5, 20);
	glRotatef(roverWheelRotation % 360, 0, 0, 1); // Robot hareket ettiğinde tekerlekler döner
	glutWireSphere(6, 6, 6);
	glPopMatrix();

	// Tekerlek sağ ön
	glPushMatrix();
	glColor3f(0, 1, 1);
	glTranslatef(10, -5, 20);
	glRotatef(roverWheelRotation % 360, 0, 0, 1); // Robot hareket ettiğinde tekerlekler döner
	glutWireSphere(6, 10, 10);
	glPopMatrix();
	//---------------------- TEKERLEK BİTİŞİ ----------------------

	// Robot rengi (Tekerlekler hariç)
	glColor3f(0, 1, 1);

	glPushMatrix(); //-------- GÖVDE VE ANTEN BAŞLANGICI --------

	// Robot gövdesi
	glPushMatrix();
	glScalef(20.0, 20.0, 40.0);
	glutWireCube(1.0);
	glPopMatrix();

	// Anten sapı (Sabit)
	glPushMatrix();
	glScalef(1.0, 15.0, 1.0);
	glTranslatef(0, 1, 0);
	glutWireCube(3.0);
	glPopMatrix();

	// Anten yatay (Dönen kısım)
	glTranslatef(0, 35, 0);
	glRotatef(angleAntenna, 0.0, 1.0, 0.0);
	glPushMatrix();
	glScalef(10.0, 1.0, 10.0);
	glutWireCube(3.0);
	glPopMatrix();

	// Anten dikey (Sabit kısım)
	glTranslatef(-13, 22, 0);
	glPushMatrix();
	glScalef(1.0, 15.0, 10.0);
	glutWireCube(3.0);
	glPopMatrix();

	glPopMatrix(); //---------- GÖVDE VE ANTEN BİTİŞİ ----------

	// Gövdeye bağlı sabit kol
	glTranslatef(20, 0, 0);
	glPushMatrix();
	glScalef(15.0, 1.0, 1.0);
	glutWireCube(3.0);
	glPopMatrix();

	// Omuz
	glTranslatef(20, 0, 0);
	glRotatef(angleShoulder - 45, 0, 0, 1);
	glTranslatef(0, 16, 0);
	glPushMatrix();
	glScalef(1.0, 12.0, 1.0);
	glutWireCube(3.0);
	glPopMatrix();

	// Dirsek
	glTranslatef(0, 17, 0);
	glRotatef(angleElbow + 60, 0, 0, 1);
	glTranslatef(17, 0, 0);
	glPushMatrix();
	glScalef(12.0, 1.0, 1.0);
	glutWireCube(3.0);
	glPopMatrix();

	// Bilek + Alt Parmak
	glPushMatrix(); //---------- BİLEK + ALT PARMAK BAŞLANGIÇ ----------

	glTranslatef(17, 0.0, 0.0);
	glRotatef(angleWrist + 90, 0, 0, 1);
	glPushMatrix();
	glScalef(8.0, 1.0, 1.0);
	glutWireCube(3.0);
	glPopMatrix();

	// Parmak Alt
	glTranslatef(-10, 0, 0);
	glRotatef(90 + angleFinger, 0, 0, 1);
	glTranslatef(-12, 0, 0);
	glPushMatrix();
	glScalef(8.0, 1.0, 1.0);
	glutWireCube(3.0);
	glPopMatrix();

	glPopMatrix(); //------------ BİLEK + ALT PARMAK BİTİŞ ------------

	// Bilek + Üst Parmak
	glPushMatrix(); //--------- BİLEK + ÜST PARMAK BAŞLANGIÇ ----------

	glTranslatef(17, 0, 0);
	glRotatef(angleWrist + 90, 0, 0, 1);
	glPushMatrix();
	glScalef(8.0, 1.0, 1.0);
	glutWireCube(3.0);
	glPopMatrix();

	// Parmak Üst
	glTranslatef(10, 0, 0);
	glRotatef(90 - angleFinger, 0, 0, 1);
	glTranslatef(-12, 0, 0);
	glPushMatrix();
	glScalef(8.0, 1.0, 1.0);
	glutWireCube(3.0);
	glPopMatrix();

	glPopMatrix(); //------------ BİLEK + ÜST PARMAK BİTİŞ ------------

	glPopMatrix(); //----------------------------------------------- ROBOT BİTİŞİ -----------------------------------------------

	glFlush();
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 0.75, 1, 1000); // Perspektif
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle(void) // Antenin sürekli dönmesini sağlayan fonksiyon
{
	idleCounter++;
	if (idleCounter % 100000 == 0)
	{
		angleAntenna += 0.5;
		display();
		idleCounter = 0;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W': // İleri
	case 'w':
		angleRover = 90; // Robotun yönünü ileri doğru çevirir
		if (boundaryZ < 180) // Robotun z ekseninde harita dışına çıkmasını engeller
		{
			roverWheelRotation += 90; // Tekerlek döndürme açısı değeri
			directionForwardBackward -= 2; // Robot hız değeri
			boundaryZ++;
			if (boundaryZ % 10 == 0 && boundaryZ != 0) // Robotun y eksenine göre yüksekliğini ayarlar
				roverAltitude++;
			display();
		}
		break;

	case 'A': // Sol
	case 'a':
		angleRover = 180; // Robotun yönünü sola doğru çevirir
		if (boundaryX > 0)  // Robotun x ekseninde harita dışına çıkmasını engeller
		{
			roverWheelRotation += 90;
			directionRightLeft -= 2;
			display();
			if (boundaryX % 10 == 0) // Robotun y eksenine göre yüksekliğini ayarlar
				roverAltitude -= 21;
			boundaryX--;
		}
		break;

	case 'S': // Geri
	case 's':
		angleRover = -90; // Robotun yönünü geriye doğru çevirir
		if (boundaryZ > 0) // Robotun z ekseninde harita dışına çıkmasını engeller
		{
			roverWheelRotation += 90;
			directionForwardBackward += 2;
			boundaryZ--;
			if (boundaryZ % 10 == 0 && boundaryZ != 0) // Robotun y eksenine göre yüksekliğini ayarlar
				roverAltitude--;
			display();
		}
		break;

	case 'D': // Sağ
	case 'd':
		angleRover = 0; // Robotun yönünü sağa doğru çevirir
		if (boundaryX < 150) // Robotun x ekseninde harita dışına çıkmasını engeller
		{
			roverWheelRotation += 90;
			directionRightLeft += 2;
			boundaryX++;
			if (boundaryX % 10 == 0) // Robotun y eksenine göre yüksekliğini ayarlar
				roverAltitude += 21;
			display();
		}

		break;

	case 'H': // Harita renklendirme
	case 'h':
		mapAltitudeStatus++; // mapAltitudeStatus değişkeninin değerine göre harita renklenir.
		if (mapAltitudeStatus % 2 == 1)
		{
			mapAltitudeStatus = 1;
			display();
		}
		else
		{
			mapAltitudeStatus = 0;
			display();
		}
		break;

	case 'O': // Tutucuların açılıp kapanmasını sağlar
	case 'o':
		if (stateFinger == 0)
		{
			angleFinger = 15;
			display();
			stateFinger++;
		}
		else
		{
			angleFinger = -15;
			display();
			stateFinger--;
		}
		break;

	case '1': // Omuz aktif (Omuz hareketleri için)
		stateShoulder = 1;
		stateElbow = 0;
		stateWrist = 0;
		break;

	case '2': // Dirsek aktif (Dirsek hareketleri için)
		stateShoulder = 0;
		stateElbow = 1;
		stateWrist = 0;
		break;

	case '3': // Bilek aktif (Bilek hareketleri için)
		stateShoulder = 0;
		stateElbow = 0;
		stateWrist = 1;
		break;

	case'+': // Açık olan parçanın yukarı hareketi
		if (stateShoulder == 1 && angleShoulder < 30)
		{
			angleShoulder += 5;
		}
		else if (stateElbow == 1 && angleElbow < 90)
		{
			angleElbow += 5;
		}
		else if (stateWrist == 1 && angleWrist < 45)
		{
			angleWrist += 5;
		}
		display();
		break;

	case'-':  // Açık olan parçanın aşağı hareketi
		if (stateShoulder == 1 && angleShoulder > -90)
		{
			angleShoulder -= 5;
		}
		else if (stateElbow == 1 && angleElbow > -45)
		{
			angleElbow -= 5;
		}
		else if (stateWrist == 1 && angleWrist > -45)
		{
			angleWrist -= 5;
		}
		display();
		break;

	}
}

void special(int key1, int x, int y)
{
	switch (key1)
	{
	case GLUT_KEY_LEFT: // Kamerayı sola doğru döndür
		angleCamera = angleCamera + 0.05;
		if (angleCamera > 360.0)
			angleCamera = 0.0;
		cameraX = cameraDistance * cos(angleCamera / 180.0*3.14);
		cameraZ = cameraDistance * sin(angleCamera / 180.0*3.14);
		gluLookAt(cameraX + 5, 0.0, cameraZ + 5, 0, 0, -150, 0, 1, 0);
		break;

	case GLUT_KEY_RIGHT: // Kamerayı sağa doğru döndür
		angleCamera = angleCamera - 0.05;
		if (angleCamera < 360.0)
			angleCamera = 0.0;
		cameraX = cameraDistance * cos(angleCamera / 180.0*3.14);
		cameraZ = cameraDistance * sin(angleCamera / 180.0*3.14);
		gluLookAt(-cameraX - 5, 0.0, -cameraZ - 5, 0, 0, -150, 0, 1, 0);
		break;

	case GLUT_KEY_UP: // Haritada ileri git
		angleCamera += 0.5;
		if (angleCamera > 360.0)
			angleCamera = 0.0;
		cameraZ = cameraDistance * sin(angleCamera / 180.0*3.14);
		gluLookAt(0.0, 0.0, -cameraZ - 5, 0, 0, -150, 0, 1, 0);
		break;

	case GLUT_KEY_DOWN: // Haritada geri git
		angleCamera -= 0.5;
		if (angleCamera < 360.0)
			angleCamera = 0.0;
		cameraZ = cameraDistance * sin(angleCamera / 180.0*3.14);
		gluLookAt(0.0, 0.0, cameraZ + 5, 0, 0, -150, 0, 1, 0);
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow(argv[0]);

	// Işık ayarları
	glEnable(GL_LIGHTING); // Işık kaynağını etkinleştir.
	GLfloat diffuseLight[] = { 0.75, 0.75, 0.75, 1 };
	GLfloat lightPosition[] = { -25, -1, -1, 1 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHT0); // LIGHT0 ışığı etkin.
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
}