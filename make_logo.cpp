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
    Color fromimage_left, fromimage_rigth;
    int i;
    double intens,intens_r ;
    //cout << "Прочитал " << image_pa.string();
    for (i=1; i<=30; ++i){
       fromimage_left = image.pixelColor(1, image.rows()-i );
       fromimage_rigth = image.pixelColor(image.columns()-1, i );
       intens_r = fromimage_rigth.intensity();
       intens = fromimage_left.intensity();
        if ((intens >= 31000 and intens <= 50000) or (intens_r >= 31000 and intens_r <= 50000))
        {
           //image = add_logo(image);
          // image.write( image_pa.string() ); //добавляет картинку
        	return true;
        }
    }
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

            } //else {cout <<  *it  << " -- without logo" <<  '\n';}
          }// файл
        }
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

