#include <ImageMagick/Magick++.h>

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

namespace fs = boost::filesystem;
using namespace std;
using namespace Magick;


bool is_logo(Image image)
{ //надо сюда передавать изображение чтоб не читать два раза
    Color cen_up,cen_bot,cen_left,cen_rigth;
    double left1,rigth1;
    double left10,rigth10;
    double left20,rigth20;
    int i;
    //int dop;
    //dop = 0;
    //bool l_true, r_true;
    //double intens,intens_r ;
    cen_up = image.pixelColor(image.columns()/2, 1 );
    cen_bot = image.pixelColor(image.columns()/2, image.rows()-1 );
    cen_left = image.pixelColor(1, image.rows()/2 );
    cen_rigth = image.pixelColor(image.columns()-1, image.rows()/2 );
    //image.pixelColor(image.columns()/2, 1, "red" );
    //image.pixelColor(image.columns()/2, image.rows()-1 , "red");
    //image.pixelColor(1, image.rows()/2 , "red");
    //image.pixelColor(image.columns()-1, image.rows()/2, "red" );
    //image.write("/home/ror/image/test.jpg");
    //cout << cen_up.intensity() << " - " << cen_bot.intensity() << " - " << cen_left.intensity() << " - " << cen_rigth.intensity() <<  '\n';
    if ((cen_up.intensity() >= 31000 and cen_up.intensity() <= 50000) or (cen_bot.intensity() >= 31000 and cen_bot.intensity() <= 50000) or (cen_left.intensity() >= 31000 and cen_left.intensity() <= 50000) or (cen_rigth.intensity() >= 31000 and cen_rigth.intensity() <= 50000)) {
    //cout << "Прочитал " << image_pa.string();
    	//skip_count = skip_count+1;
    	cout << "!!!Skipped";
    }
    else {
    for (i=1; i<=30; ++i){
    	//l_true = false;
    	//r_true = false;
       left1 = image.pixelColor(1, image.rows()-i ).intensity();
       rigth1 = image.pixelColor(image.columns()-1, i ).intensity();
       left10 = image.pixelColor(10, image.rows()-i ).intensity();
       rigth10 = image.pixelColor(image.columns()-10, i ).intensity();
       left20 = image.pixelColor(20, image.rows()-i ).intensity();
       rigth20 = image.pixelColor(image.columns()-20, i ).intensity();
       //image.pixelColor(20, image.rows()-i , "red");
       //image.pixelColor(image.columns()-20, i, "red" );
       //intens_r = fromimage_rigth.intensity();
       //intens = fromimage_left.intensity();
       //cout << intens << " - " << intens_r << "-";
        if ((left1 >= 31000 and left1 <= 50000) or (rigth1 >= 31000 and rigth1 <= 50000)
        	 or (left10 >= 31000 and left10 <= 50000) or (rigth10 >= 31000 and rigth10 <= 50000)
        	 or (left20 >= 31000 and left20 <= 50000) or (rigth20 >= 31000 and rigth20 <= 50000)
        )//if
        {
        	//image = add_logo(image);
        	//dop = dop +1;
        	//image.write( "~image/" + dop +"im.jpg" ); //добавляет картинку
        	return true;
        }

    }
    //dop = dop +1;
    //image.write( "/home/ror/image/"+convertInt(dop)+"im.jpg" );
    // покрасим проход
    //image.write( "/home/ror/image/im.jpg" );
    } // если есть серый фон
    return false;
}


int main( int argc, char ** argv)
{
  if (argc < 2)
  {
    cout << "Usage: please path\n";
    return 1;
  }
  fs::path p (argv[1]);   // p reads clearer than argv[1] in the following code
//инициируем лого
	fs::path logo_pa="/home/ror/image/logo/";
	const char* vert_logo = "vert_logo.psd";
	const char* hor_logo = "hor_logo.psd";
	Image h_logo(logo_pa.string()+hor_logo);
	Image v_logo(logo_pa.string()+vert_logo);
	Image logo;
	Geometry placement(0,0,0,0);
	int fi_co, lo_co ;
	fi_co = 0;
	lo_co = 0;
try {
    //cout << "Read images ..." << endl;
     if (fs::exists(p))    // does p actually exist?
    {
      if (fs::is_directory(p))        // is p is a irectory?
      {
        fs::path path_t;
        typedef vector<fs::path> vec;             // store paths,
        vec v;                                // so we can sort them later
        copy(fs::directory_iterator(p), fs::directory_iterator(), back_inserter(v));
        for (vec::const_iterator it(v.begin()), it_end(v.end()); it != it_end; ++it)
        {
            if (fs::is_regular_file(*it))
            {
            fi_co = fi_co+1;
            fs::path	image_pa = *it;
            Image image (image_pa.string()) ;
             if (is_logo(image)){
            	//cout <<  image_pa.string()  << "     is with logo" <<  '\n';
            	Geometry size_pa = image.size();
                size_pa.aspect(true);
            	int x = image.rows();
                int y = image.columns();
                if (x<y){
                	logo = h_logo;
                }else {logo = v_logo;}
                logo.scale(size_pa);
            	image.composite( logo, placement, OverCompositeOp );
            	image.write(image_pa.string());
            	lo_co = lo_co + 1;
            } //else {cout <<  *it  << " -- without logo" <<  '\n';}
          }// файл
        }
        cout <<  "For job = "  << fi_co <<  " -- with logo - " << lo_co << '\n';
      }
    }
    else
      cout << p << " does not exist\n";


    return 0;

}
catch( exception &error_ )
  {
    cout << "Caught exception: " << error_.what() << endl;
    return 1;
  }

return 0;
}

