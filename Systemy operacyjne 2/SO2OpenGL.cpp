
/*
Zadanie drugie 
Narysować poziomą kreskę w połowie. Kulki mogą przekroczyć tą kreskę tylko wtedy, gdy 
przepuści je prostokąt.Przed dotarciem prostokąta kulki oczekują na przepuszczenie ich.
*/
/*
Zadanie trzecie
Wyświetlić liczbę zablokowonaych kulek  u góry i u dołu
Liczba ta powinna być obliczana za każdym razem, gdy kulka się zablokuje lub prostokąt ją odblokuje.
*/
#define _USE_MATH_DEFINES
#include<GL/gl.h>
#include<GL/glut.h>
#include<math.h>
#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<memory>
#include<string>
#include<chrono>
#include<condition_variable>

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;
 struct Ball{   //Dane kulki
    int number;
    float x;
    float y;
    float x_speed;
    float y_speed;
    float r,g,b;
    GLuint texture;
    bool lock=false;
};

typedef float point3[3];  
const int max_balls=20;

condition_variable cv[max_balls];
mutex m[max_balls];
bool used[max_balls];
mutex used_mutex;
bool lock_table[max_balls];

vector<Ball> b_vec;
mutex b_vec_mutex;

vector<unique_ptr<thread>> t_vec;
vector<unique_ptr<thread>> t_vector;
int max_speed=2;
bool memory_deleted=false;

//Położenie poruszającego się prostokąta
point3 a={-30.0f,10.0f};
point3 b={30.0f,10.0f};
point3 c={30.0f,-10.0f};
point3 d={-30.0f,-10.0f};
//Przesunięcie prostokąta
float rec_tr=0.0f;
bool rec_right;
float rec_speed=0.5f;
mutex rec_mutex;

float *circle_x;
float *circle_y;

float rec_x=160.0f;
float rec_y=85.0f;
float rec_x_max=rec_x-4.0f;
float rec_y_max=rec_y-4.0f;
float half=-4.0f;
float plus_half=4.0f;
bool stop_program=false;
bool stop_program2=false;
bool stop_program3=false;

void rectangle_movement();
void ball_creating();
void ball_move(Ball b);
void refresh();
thread ball_creating_t(ball_creating);
thread r_movement_t(rectangle_movement);
const int t_size=25;
int locked_up=0;
int locked_down=0;
mutex counter_mutex;
mutex delete_list_mutex;
vector<thread::id> delete_id;
GLuint tab[t_size];
GLbyte* LoadTGAImage(const char* FileName, GLint* ImWidth, GLint* ImHeight, GLint* ImComponents, GLenum* ImFormat)
{
#pragma pack(1)           
    typedef struct
    {
        GLbyte    idlength;
        GLbyte    colormaptype;
        GLbyte    datatypecode;
        unsigned short    colormapstart;
        unsigned short    colormaplength;
        unsigned char     colormapdepth;
        unsigned short    x_orgin;
        unsigned short    y_orgin;
        unsigned short    width;
        unsigned short    height;
        GLbyte    bitsperpixel;
        GLbyte    descriptor;
    }TGAHEADER;
#pragma pack(8)

    FILE* pFile;
    TGAHEADER tgaHeader;
    unsigned long lImageSize;
    short sDepth;
    GLbyte* pbitsperpixel = NULL;

    *ImWidth = 0;
    *ImHeight = 0;
    *ImFormat = GL_BGR_EXT;
    *ImComponents = GL_RGB8;

    pFile = fopen(FileName, "rb");
    if (pFile == NULL)
        return NULL;

    fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);

    *ImWidth = tgaHeader.width;
    *ImHeight = tgaHeader.height;
    sDepth = tgaHeader.bitsperpixel / 8;

    if (tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
        return NULL;

    lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

    pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));

    if (pbitsperpixel == NULL)
        return NULL;

    if (fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
    {
        free(pbitsperpixel);
        return NULL;
    }

    switch (sDepth)
    {
    case 3:
        *ImFormat = GL_BGR_EXT;
        *ImComponents = GL_RGB8;
        break;
    case 4:
        *ImFormat = GL_BGRA_EXT;
        *ImComponents = GL_RGBA8;
        break;
    case 1:
        *ImFormat = GL_LUMINANCE;
        *ImComponents = GL_LUMINANCE8;
        break;
    };
    fclose(pFile);
    return pbitsperpixel;
}
GLuint load_texture(string fn) {
    GLbyte* pBytes;
    GLint ImWidth, ImHeight, ImComponents;
    GLenum ImFormat;
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glEnable(GL_CULL_FACE);        
    pBytes = LoadTGAImage(fn.c_str(), &ImWidth, &ImHeight, &ImComponents, &ImFormat);    //Wywołanie funkcji pobierającej obraz tekstury z pliku

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);    //Zdefiniowanie tekstury 2-D

    free(pBytes);      
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

float return_float_from0to1() {
    int x = rand() % 10001;
    return 1.00f * x / 10000.00f;
}
float return_float_from0to1_2() {
    int x = rand() % 10000;
    return 1.00f * x / 10000.00f;
}
bool random_bool() {
    int x = rand()% 2;
    if(x%2==0)return true;
    else return false;
}

void ball_creating(){
    srand(time(NULL));
    int x;
    int vec_size;
    bool less=false;
    while(true){
        if(stop_program==true) {
            return;
        }
        delete_list_mutex.lock();
        int end=t_vec.size();
        thread::id temp_id;
        while (delete_id.size()>0){
            temp_id=delete_id.back();
            for(int i=0;i<end;i++){
                if((*(t_vec[i])).get_id()==temp_id){
                    
                    if((*(t_vec[i])).joinable()){
                        (*(t_vec[i])).join();
                        t_vec.erase(t_vec.begin()+i);
                        i--;
                        end=t_vec.size();
                    }
                    break;
                }
            }
            delete_id.pop_back();
        }
        delete_list_mutex.unlock();
        x=rand()%100;
        if(x<30){

            b_vec_mutex.lock();
            if(b_vec.size()<max_balls) less =true;
            else less = false;
            b_vec_mutex.unlock();

            if(less==true){
                Ball b;
                b.x=rand()%(int(rec_x-4.0f))+return_float_from0to1();
                if(random_bool()) b.x*=-1.0f;
                b.y=rand()%(int(rec_y-4.0f))+return_float_from0to1();
                if(random_bool()) b.y*=-1.0f;
                b.x_speed=rand()%max_speed+return_float_from0to1();
                if(b.x_speed==0.0f)b.x_speed+=0.01f;
                if(random_bool()) b.x_speed*=-1.0f;
                b.y_speed=rand()%max_speed+return_float_from0to1();
                if(b.y_speed==0.0f)b.y_speed+=0.01f;
                if(random_bool()) b.y_speed*=-1.0f;
                b.r=return_float_from0to1_2();
                b.g=return_float_from0to1_2();
                b.b=return_float_from0to1_2();
                b.texture=tab[(rand()%t_size)];
                b.lock=false;
                used_mutex.lock();
                for(int i=0;i<max_balls;i++){
                    if(used[i]==false){
                        b.number=i;
                        used[i]= true;
                        break;
                    }
                }
                used_mutex.unlock();
                b_vec_mutex.lock();
                b_vec.push_back(b);
                b_vec_mutex.unlock();
      
                t_vec.emplace_back(std::make_unique<thread>(ball_move,b));    
            }
            x=rand()%971+30;
            this_thread::sleep_for(milliseconds{x});
        }
    }
}
void ball_move(Ball b){
    if(stop_program2==true) {
        return;
    }
    float x_temp,y_temp;
        
    int pos;
    int counter=0;
    float x_position_before;
    float y_position_before;
    float difference;
    while(true){

        b_vec_mutex.lock();
        auto it=b_vec.begin();
        for( it;it!=b_vec.end();it++){
            if(it->b == b.b&&it->g == b.g&&
            it->r == b.r&&it->x == b.x&&
            it->x_speed == b.x_speed&&
            it->y == b.y&&it->y_speed == 
            b.y_speed      
            ){
                break;
            }
        }
        
        if(stop_program2==true) {
            used_mutex.lock();
             used[it->number] = false;
             used_mutex.unlock();
            b_vec.erase(it);
            b_vec_mutex.unlock();
            return;
        }
        if(counter>=6){ 
             used_mutex.lock();
             used[it->number] = false;
             used_mutex.unlock();
            b_vec.erase(it);
            b_vec_mutex.unlock();
            delete_list_mutex.lock();
            delete_id.emplace_back(this_thread::get_id());
            delete_list_mutex.unlock();
            return;
        }
        b.lock=it->lock;
        
        b_vec.erase(it);
        x_position_before=b.x;
        y_position_before=b.y;
        if(b.x_speed>0.0f && b.y_speed>0.0f){
            if(b.x+b.x_speed<=rec_x_max){
                if(b.y+b.y_speed<=rec_y_max){
                    b.x+=b.x_speed;
                    b.y+=b.y_speed;
                    if(y_position_before < half && b.y >= half){
                                                 
                            difference=half-y_position_before;
                            b.y=half;
                            b.x=x_position_before+(difference/b.y_speed)*b.x_speed;
                            b.lock=true;
                    }
                }else{
                    y_temp=rec_y_max-b.y-b.y_speed;
                    b.y=rec_y_max-y_temp;
                    b.x+=b.x_speed;
                    b.y_speed*=-1.0f;
                    counter++;
                }
            }else{
                if(b.y+b.y_speed<=rec_y_max){
                   
                    if(y_position_before < half && b.y >= half){
                                                 
                        difference=half-y_position_before;
                        b.y=half;
                        b.x=rec_x_max-(x_position_before+(difference/b.y_speed)*b.x_speed)+rec_x_max;
 
                        b.lock=true;
                    }else{
                        x_temp=rec_x_max-b.x-b.x_speed;
                        b.x=rec_x_max-x_temp;
                        b.y+=b.y_speed;
                      
                    }
                    b.x_speed*=-1.0f;
                    counter++;
                }else{
                    x_temp=rec_x_max-b.x-b.x_speed;
                    y_temp=rec_y_max-b.y-b.y_speed;
                    b.x=rec_x_max-x_temp;
                    b.y=rec_y_max-y_temp;
                    b.x_speed*=-1.0f;
                    b.y_speed*=-1.0f;
                    counter+=2;
                }
            }
        }
        else if(b.x_speed>0.0f && b.y_speed<0.0f){
            if(b.x+b.x_speed<=rec_x_max){
                if(b.y+b.y_speed>=-rec_y_max){
                    b.x+=b.x_speed;
                    b.y+=b.y_speed;
                    if(y_position_before > plus_half && b.y <= plus_half){
                                                 
                            difference=y_position_before-plus_half;
                            b.y=plus_half;
                            b.x=x_position_before+(difference/b.y_speed)*b.x_speed;
                            b.lock=true;
                    }
                }else{
                    y_temp=-rec_y_max-b.y-b.y_speed;
                    b.y=-rec_y_max+y_temp;
                    b.x+=b.x_speed;
                    b.y_speed*=-1.0f;
                    counter++;
                }
            }else{
                if(b.y+b.y_speed>=-rec_y_max){
                    if(y_position_before > plus_half && b.y <= plus_half){
                                                 
                        difference=y_position_before-plus_half;
                        b.y=plus_half;
                        b.x=rec_x_max-(x_position_before+(difference/b.y_speed)*b.x_speed)+rec_x_max;

                        b.lock=true;
                    }
                    else{
                    x_temp=rec_x_max-b.x-b.x_speed;
                    b.x=rec_x_max+x_temp;
                    b.y+=b.y_speed;
                    }
                    b.x_speed*=-1.0f;
                    counter++;
                }else{
                    x_temp=rec_x_max-b.x-b.x_speed;
                    y_temp=-rec_y_max-b.y-b.y_speed;
                    b.x=rec_x_max+x_temp;
                    b.y=-rec_y_max+y_temp;
                    b.x_speed*=-1.0f;
                    b.y_speed*=-1.0f;
                    counter+=2;
                }
            }
        }
        else if(b.x_speed<0.0f && b.y_speed>0.0f){
            if(b.x+b.x_speed>=-rec_x_max){
                if(b.y+b.y_speed<=rec_y_max){
                    b.x+=b.x_speed;
                    b.y+=b.y_speed;
                    if(y_position_before < half && b.y >= half){
                                                 
                            difference=half-y_position_before;
                            b.y=half;
                            b.x=x_position_before+(difference/b.y_speed)*b.x_speed;
                            b.lock=true;

                    }
                }else{
                    y_temp=rec_y_max-b.y-b.y_speed;
                    b.y=rec_y_max+y_temp;
                    b.x+=b.x_speed;
                    b.y_speed*=-1.0f;
                    counter++;
                }
            }else{
                if(b.y+b.y_speed<=rec_y_max){
                     if(y_position_before < half && b.y >= half){
                                                 
                        difference=half-y_position_before;
                        b.y=half;
                        b.x=-rec_x_max+(x_position_before+(difference/b.y_speed)*b.x_speed)-rec_x_max;
                        b.lock=true;

                    }
                    else{
                    x_temp=-rec_x_max-b.x-b.x_speed;
                    b.x=-rec_x_max+x_temp;
                    b.y+=b.y_speed;
                    }
                    b.x_speed*=-1.0f;
                    counter++;
                }else{
                    x_temp=-rec_x_max+b.x+b.x_speed;
                    y_temp=rec_y_max-b.y-b.y_speed;
                    b.x=-rec_x_max+x_temp;
                    b.y=rec_y_max+y_temp;
                    b.x_speed*=-1.0f;
                    b.y_speed*=-1.0f;
                    counter+=2;
                }
            }
        }else{
            if(b.x+b.x_speed>=-rec_x_max){
                if(b.y+b.y_speed>=-rec_y_max){
                    b.x+=b.x_speed;
                    b.y+=b.y_speed;
                    if(y_position_before > plus_half && b.y <= plus_half){
                                                 
                            difference=-plus_half+y_position_before;
                            b.y=plus_half;
                            b.x=x_position_before+(difference/b.y_speed)*b.x_speed;
                            b.lock=true;

                    }
                }else{
                    y_temp=-rec_y_max-b.y-b.y_speed;
                    b.y=-rec_y_max+y_temp;
                    b.x+=b.x_speed;
                    b.y_speed*=-1.0f;
                    counter++;
                }
            }else{
                if(b.y+b.y_speed>=-rec_y_max){
                    if(y_position_before > plus_half && b.y <= plus_half){
                                                 
                        difference=plus_half-y_position_before;
                        b.y=plus_half;
                        b.x=-rec_x_max+(x_position_before+(difference/b.y_speed)*b.x_speed)-rec_x_max;
                        b.lock=true;
                    }else{
                    x_temp=-rec_x_max-b.x-b.x_speed;
                    b.x=-rec_x_max+x_temp;
                    b.y+=b.y_speed;
                    }
                    b.x_speed*=-1.0f;
                    counter++;
                }else{
                    x_temp=-rec_x_max-b.x-b.x_speed;
                    y_temp=-rec_y_max-b.y-b.y_speed;
                    b.x=-rec_x_max+x_temp;
                    b.y=-rec_y_max+y_temp;
                    b.x_speed*=-1.0f;
                    b.y_speed*=-1.0f;
                    counter+=2;
                }
            }
        }
        b_vec.push_back(b);

    b_vec_mutex.unlock();
    if(b.lock==true){
        unique_lock<mutex> lk(m[b.number]);
        counter_mutex.lock();
        if(b.y>0) locked_up++;
        else locked_down++;
        counter_mutex.unlock();

        lock_table[b.number] = true;
        cv[b.number].wait(lk);

    }
    this_thread::sleep_for(milliseconds{10});

    }
}
void drawBall(float x,float y,float r, float g, float b,GLuint tex){
    glBindTexture(GL_TEXTURE_2D,tex);
    float first,second,r2=9.0f;
    glColor3f(r,g,b);
    glPushMatrix();
    glTranslatef(x,y,0.0f);
    glBegin(GL_TRIANGLES);
    for(int i=0;i<99;i++){
        
        glTexCoord2f(circle_x[i+1]/16.0f+1/2.0f,circle_y[i+1]/16.0f+1/2.0f);
        glVertex2f(circle_x[i+1],circle_y[i+1]);
        glTexCoord2f(circle_x[i]/16.0f+1/2.0f,circle_y[i]/16.0f+1/2.0f);
        glVertex2f(circle_x[i],circle_y[i]);
        glTexCoord2f(0.5f,0.5f);
        glVertex2f(0.0f,0.0f);

        glTexCoord2f(-circle_x[i]/16.0f+1/2.0f,circle_y[i]/16.0f+1/2.0f);
        glVertex2f(-circle_x[i],circle_y[i]);
        glTexCoord2f(-circle_x[i+1]/16.0f+1/2.0f,circle_y[i+1]/16.0f+1/2.0f);
        glVertex2f(-circle_x[i+1],circle_y[i+1]);
        glTexCoord2f(0.5f,0.5f);
        glVertex2f(0.0f,0.0f);   
        
        glTexCoord2f(0.5f,0.5f);
        glVertex2f(0.0f,0.0f);
        glTexCoord2f(-circle_x[i+1]/16.0f+1/2.0f,-circle_y[i+1]/16.0f+1/2.0f);
        glVertex2f(-circle_x[i+1],-circle_y[i+1]);
        glTexCoord2f(-circle_x[i]/16.0f+1/2.0f,-circle_y[i]/16.0f+1/2.0f);
        glVertex2f(-circle_x[i],-circle_y[i]);       
        
        glTexCoord2f(circle_x[i]/16.0f+1/2.0f,-circle_y[i]/16.0f+1/2.0f);
        glVertex2f(circle_x[i],-circle_y[i]);        
        glTexCoord2f(circle_x[i+1]/16.0f+1/2.0f,-circle_y[i+1]/16.0f+1/2.0f);
        glVertex2f(circle_x[i+1],-circle_y[i+1]);
        glTexCoord2f(0.5f,0.5f);
        glVertex2f(0.0f,0.0f);
    } 
    glEnd();
    glPopMatrix();
}
void drawRectangle(){
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.83f,0.83f,0.83f); 
    
    glPushMatrix();
    glTranslatef(rec_tr,0.0f,0.0f);
    glBegin(GL_QUADS);
    glVertex2fv(b);
    glVertex2fv(a);    
    glVertex2fv(d);
    glVertex2fv(c);
    
    glEnd();
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);

} 
void drawBigRectangle(){
   glDisable(GL_TEXTURE_2D);
   glColor3f(1.0f,1.0f,1.0f);
   glRectf(-rec_x,-rec_y,rec_x,rec_y);
   glEnable(GL_TEXTURE_2D);
} 
void RenderScene() {    

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawBigRectangle();  
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINES);
    glVertex2f(-rec_x,0.0f);
    glVertex2f(rec_x,0.0f);

    glEnd();

    rec_mutex.lock(); 
    drawRectangle();
    rec_mutex.unlock();

    b_vec_mutex.lock();
   for(Ball ball:b_vec){
      drawBall(ball.x,ball.y,ball.r,ball.g,ball.b,ball.texture); 
       
    }
    counter_mutex.lock();
    int t1=locked_down % 10;
    int t2=(locked_down-t1)/10;
    int t3=locked_up % 10;
    int t4=(locked_up-t3)/10;
    counter_mutex.unlock();
    glColor3f(0.0f,0.0f,0.0f);
    glRasterPos2f(100.,-95.);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'0'+t2);

    glRasterPos2f(105.,-95.);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'0'+t1);

    glRasterPos2f(100.,90.);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'0'+t4);

    glRasterPos2f(105.,90.);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'0'+t3); 

   b_vec_mutex.unlock();

    glFlush();

    glutSwapBuffers();
}
void ChangeSize(GLsizei horizontal, GLsizei vertical) {
    GLfloat AspectRatio;
    if (vertical == 0)
        vertical = 1;
    glViewport(0, 0, horizontal, vertical);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
    if (horizontal <= vertical)
        glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
    else
        glOrtho(-100.0 * AspectRatio, 100.0 * AspectRatio, -100.0, 100.0, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
    
}
void MyInit(void){
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
     string file_name;
    for(int i=0;i<t_size;i++){
        file_name="";
        file_name.append(to_string(i+1));
        file_name.append( ".tga"); 
         
        tab[i] = load_texture(file_name);
    }
}
int ifd=0;

void initialize(){
    circle_x=new float[100];
    circle_y=new float[100];
    for(int i=0;i<100;i++){
        circle_x[i]=i/99.0f*4.0f;
        circle_y[i]=sqrt(16.0f-circle_x[i]*circle_x[i]);
    }

}
void delete_memory(){
    delete [] circle_x;
    delete [] circle_y;
}
float get_rec_speed(){
    float x=float(rand()%3)+return_float_from0to1();
    if(x==0.0f) x+=0.1f;
    return x;
}

void rectangle_movement(){
    bool direction_right_before;
    float first_x_coordinate,second_x_coordinate;
    float x_coordinate_before;
    float diff;
    rec_right=random_bool;
    rec_speed=get_rec_speed();

    while(true){  
        if(stop_program==true) {
            return;
        }
        rec_mutex.lock();    
        direction_right_before=rec_right;
        x_coordinate_before=rec_tr;
        if(rec_right){
            if(rec_tr+rec_speed<=rec_x-30.0f){
                rec_tr=rec_tr+rec_speed;
            }else{
                diff=rec_tr+rec_speed-rec_x+30.0f;
                rec_tr=rec_x-30.0f-diff;
                rec_speed=get_rec_speed();
                rec_right=false;
            }
        }else{
            if(rec_tr-rec_speed>=-rec_x+30.0f){
                rec_tr=rec_tr-rec_speed;
            }else{
                diff=-rec_tr+rec_speed-rec_x+30.0f;
                rec_tr=-rec_x+30.0f-diff;
                rec_speed=get_rec_speed();
                rec_right=true;
            }
        }
        rec_mutex.unlock();
        if(direction_right_before==false and rec_right==false){
            first_x_coordinate=rec_tr-30.0f;
            second_x_coordinate=x_coordinate_before+30.0f;
        }else if(direction_right_before==true and rec_right==true){
            first_x_coordinate=x_coordinate_before-30.0f;
            second_x_coordinate=rec_tr+30.0f;
        }else if(direction_right_before==true and rec_right==false){
            if(rec_tr<=x_coordinate_before){
                first_x_coordinate=rec_tr-30.0f;
                second_x_coordinate=rec_x;
            }else{
                first_x_coordinate=x_coordinate_before-30.0f;
                second_x_coordinate=rec_x;
            }
        }else if(direction_right_before==false and rec_right==true){
            if(rec_tr<=x_coordinate_before){
                first_x_coordinate=-rec_x;
                second_x_coordinate=x_coordinate_before+30.0f;
            }else{
                first_x_coordinate=-rec_x;
                second_x_coordinate=rec_tr+30.0f;
            }
        }
        
        b_vec_mutex.lock();
        auto it=b_vec.begin();
        int y;
        for( it;it!=b_vec.end();it++){

            unique_lock<mutex> lk(m[it->number]);
            if( lock_table[it->number]==true && it->x>=first_x_coordinate && it->x<=second_x_coordinate){
                y= it->y;
                counter_mutex.lock();
                if(y>0) locked_up--;
                else locked_down--;
                counter_mutex.unlock();
                lock_table[it->number]=false;
                it->lock=false;
                cv[it->number].notify_one();
            } 
        }
        b_vec_mutex.unlock();

        this_thread::sleep_for(milliseconds{10});
    }
}
void stop(){        //Funkcja kończy wątki

    stop_program=true;
    if(ball_creating_t.joinable()){
        ball_creating_t.join();
    }
    if(r_movement_t.joinable()){
        r_movement_t.join();
    }

    stop_program2=true;
    stop_program3=true;
    for(int i=0;i<max_balls;i++) cv[i].notify_one();

    for(int i=0;i<t_vec.size();i++){
        if((*t_vec[i]).joinable()){

            (*t_vec[i]).join();
        }
    }
   if(memory_deleted==false){
        delete_memory();
        memory_deleted=true;
   }
    return;
}
void keyboard(unsigned char key,int x,int y){
    switch(key)
    {
        case 101:   //przycisk e -end                            
            exit(0);
            break;
    }
}
void idle(void){

     glutPostRedisplay();
    
    }
int main(int argc, char *argv[]){
    for(int i=0;i<max_balls;i++) {
        used[i] = false;
        lock_table[i]=false;
    }
    srand(time(NULL));
    initialize();  
    ball_creating_t.detach();   //wątek odpowiedzialny za tworzenie kulek
    r_movement_t.detach();      //wątek odpowiedzialny za poruszanie prostokątem
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);   
    glutInitWindowSize(700, 400);   
    glutInit(&argc, argv);               
    glutCreateWindow("SO2 projekt");        
    glutDisplayFunc(RenderScene);        
    glutKeyboardFunc(keyboard);    
    glutIdleFunc(idle);       
    glutReshapeFunc(ChangeSize);
    MyInit();
    atexit(stop);
    glutMainLoop();

    return 0;
}