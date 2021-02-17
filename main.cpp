#include <GL/glut.h>

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


/*
Function to set Background and to set depth-test
*/

void init ()
{
    glClearColor (0.0f,0.0f,0.0f,1.0f);
    glClearDepth (1.0f);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

vector<string> stringSplit (string input){
    vector<string> output;
    string temp = "";

    for(int i=0;i<input.length();i++){
        if(input[i] == ' '){
            output.push_back(temp);
            temp = "";
        }
        else{
            temp += input[i];
        }
    }
    if(temp != ""){
        output.push_back(temp);
    }
    return output;
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
    glLoadIdentity();                 // Reset the model-view matrix
    glScalef(0.3f,0.3f,0.3f);  // Move right and into the screen

    ifstream file;
    file.open("wolf02.off");
    string text;
    getline(file, text);
    getline(file, text);

    vector<string> details = stringSplit(text);
    int Vertices = stoi(details[0]); //atoi converts string to integer
    int Faces = stoi(details[1]);
    int Edges = stoi(details[2]);

    vector<vector<string>> vertices(Vertices);
    for(int i=0;i<Vertices;i++){
        getline(file, text);
        vertices[i] = stringSplit(text);
    }
    vector<vector<string>> faces(Faces);
    for(int i=0;i<Faces;i++){
        getline(file, text);
        faces[i] = stringSplit(text);
    }

    file.close();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 1.0f, 0.0f);

    for(int i=0;i<Faces;i++){
        int v1 = stoi(faces[i][1]);
        int v2 = stoi(faces[i][2]);
        int v3 = stoi(faces[i][3]);
        glVertex3f(stof(vertices[v1][0])/10, stof(vertices[v1][1])/10, stof(vertices[v1][2])/10);
        glVertex3f(stof(vertices[v2][0])/10, stof(vertices[v2][1])/10, stof(vertices[v2][2])/10);
        glVertex3f(stof(vertices[v3][0])/10, stof(vertices[v3][1])/10, stof(vertices[v3][2])/10);
        }
    glEnd();
    glutSwapBuffers();
}

void reshape(int  width, int height) {

   if (height == 0) height = 1;
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(50, 50);
   glutCreateWindow("Assignment-2");
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   init();
   glutMainLoop();
   return 0;
}
