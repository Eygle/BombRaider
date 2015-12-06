#ifndef __GUIIMAGE__
#define __GUIIMAGE__

#include <string>

#include <GDL/Image.hpp>

namespace Graphic
{
  struct ImagePosition
  {
    float		x1_;
    float		y1_;
    float		x2_;
    float		y2_;
    ImagePosition(float x1 = 0, float y1 = 0, float x2 = 0, float y2 = 0);
    void	setPos(float, float, float, float);
  };

  class Image
  {
    gdl::Image		image_;
  public :
    Image(std::string const &path);
    Image();
    ~Image();
    Image	&operator=(Image const &);

    gdl::Image	const &getImage() const;
    void	bind();
  };

  class GuiImage
  {
  private:
    ImagePosition	pos_;
    Image		*image_;

  public :
    GuiImage(ImagePosition	pos, Image *image = 0);
    ~GuiImage();

    void	draw();
    void	draw(int percent);
    void	setImage(Image *image);
    void	setImagePosition(const ImagePosition &pos);
    void	setX2(int);
    Image	*getImage() const;
  };
};

#endif
