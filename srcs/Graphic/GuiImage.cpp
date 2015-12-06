#include <GL/gl.h>
#include <GL/glu.h>
#include "Graphic/GuiImage.hpp"

namespace Graphic
{
  ImagePosition::ImagePosition(float x1, float y1, float x2, float y2)
    : x1_(x1), y1_(y1), x2_(x2), y2_(y2)
  {
  }

  void	ImagePosition::setPos(float x1, float y1, float x2, float y2)
  {
    this->x1_ = x1;
    this->y1_ = y1;
    this->x2_ = x2;
    this->y2_ = y2;
  }
  // Image

  Image::Image(std::string const &path)
    : image_(gdl::Image::load(path))
  {
  }

  Image::Image()
  {
  }

  Image::~Image()
  {
  }

  Image	&Image::operator=(Image const &other)
  {
    this->image_ = other.getImage();
    return *this;
  }

  gdl::Image	const &Image::getImage() const
  {
    return this->image_;
  }

  void	Image::bind()
  {
    this->image_.bind();
  }

  // GuiImage

  GuiImage::GuiImage(ImagePosition pos, Image *image)
    : pos_(pos), image_(image)
  {
  }

  GuiImage::~GuiImage()
  {
  }

  void	GuiImage::setImage(Image *image)
  {
    this->image_ = image;
  }

  void	GuiImage::setImagePosition(const ImagePosition &pos)
  {
    this->pos_ = pos;
  }

  void	GuiImage::setX2(int x2)
  {
    this->pos_.x2_ = x2;
  }

  void	GuiImage::draw()
  {
    if (this->image_)
      {
	this->image_->bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);
	glVertex3f(this->pos_.x1_, this->pos_.y1_, 0.0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(this->pos_.x1_,this->pos_.y2_,0.0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(this->pos_.x2_,this->pos_.y2_,0.0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(this->pos_.x2_,this->pos_.y1_,0.0);
	glEnd();
      }
  }
  void	GuiImage::draw(int percent)
  {
    double perce = 1 - (percent / 100.0);
    double height = (this->pos_.y2_ - this->pos_.y1_) * perce;

    if (this->image_)
      {
	this->image_->bind();
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, perce);
	glVertex3f(this->pos_.x1_, this->pos_.y1_ + height, 0.0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(this->pos_.x1_,this->pos_.y2_,0.0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(this->pos_.x2_,this->pos_.y2_,0.0);
	glTexCoord2f(1.0, perce);
	glVertex3f(this->pos_.x2_,this->pos_.y1_ + height,0.0);
	glEnd();
      }
  }

  Image	*GuiImage::getImage() const
  {
    return this->image_;
  }
}
