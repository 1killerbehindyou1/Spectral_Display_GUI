#ifndef _Transform_
#define _Transform_

#define LED_RULER_LENTH 128
#define IMG_RES 181

class Tpixel
{
   int m_color;
   int m_x;
   int m_y;
   double m_angle;
   double m_module;

   public:
   void set_color(int i)
   {
       m_color = i;
   }
   int show_color()
   {
       return m_color;
   }
   int show_x_corrd()
   {
       return m_x;
   }
    int show_y_corrd()
   {
       return m_y;
   }
   void set_cordinate(int x, int y)
   {
        m_x = x;
        m_y = y;
   }

};

class Tlistwa
{
   
}; 

class Ttransform
{
private:
    Tpixel raw_matrix[IMG_RES][IMG_RES];
    int exp_matrix[6][360]={0};

public:
    Ttransform();
    void load_data();
    void trans();
    void sort();
    void show();
    void adjust();
};
#endif

