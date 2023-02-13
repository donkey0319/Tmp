#include <iostream>
#include "Image.h"

Image::Image()
{
    PNG();
};
Image::Image(unsigned int width, unsigned int height) : PNG(width, height){};
void Image::darken()
{
    for (unsigned int w = 0; w < width(); w++)
    {
        for (unsigned int h = 0; h < height(); h++)
        {
            cs225::HSLAPixel &pixel = getPixel(w, h);
            pixel.l -= 0.1;
            if (pixel.l < 0)
                pixel.l = 0;
        }
    }
};
void Image::darken(double amount)
{
    for (unsigned int w = 0; w < width(); w++)
    {
        for (unsigned int h = 0; h < height(); h++)
        {
            cs225::HSLAPixel &pixel = getPixel(w, h);
            pixel.l -= amount;
            if (pixel.l < 0)
                pixel.l = 0;
        }
    }
};
void Image::desaturate()
{
    for (unsigned int w = 0; w < width(); w++)
    {
        for (unsigned int h = 0; h < height(); h++)
        {
            cs225::HSLAPixel &pixel = getPixel(w, h);
            pixel.s -= 0.1;
            if (pixel.s < 0)
                pixel.s = 0;
        }
    }
};
void Image::desaturate(double amount)
{
    for (unsigned int w = 0; w < width(); w++)
    {
        for (unsigned int h = 0; h < height(); h++)
        {
            cs225::HSLAPixel &pixel = getPixel(w, h);
            pixel.s -= amount;
            if (pixel.s < 0)
                pixel.s = 0;
        }
    }
};
void Image::grayscale()
{
    for (unsigned int w = 0; w < width(); w++)
    {
        for (unsigned int h = 0; h < height(); h++)
        {
            cs225::HSLAPixel &pixel = getPixel(w, h);
            pixel.s = 0;
        }
    }
};
void Image::illinify()
{
    // orange = 11; blue 216

    for (unsigned int w = 0; w < width(); w++)
    {
        for (unsigned int h = 0; h < height(); h++)
        {
            cs225::HSLAPixel &pixel = getPixel(w, h);
            if (pixel.h <= 102.5 || pixel.h >= 293.5)
                pixel.h = 11;
            else
                pixel.h = 216;
        }
    }
};
void Image::lighten()
{
    for (unsigned int w = 0; w < width(); w++)
    {
        for (unsigned int h = 0; h < height(); h++)
        {
            cs225::HSLAPixel &pixel = getPixel(w, h);
            pixel.l += 0.1;
            if (pixel.l > 1)
                pixel.l = 1;
        }
    }
};
void Image::lighten(double amount)
{
    for (unsigned int w = 0; w < width(); w++)
    {
        for (unsigned int h = 0; h < height(); h++)
        {
            cs225::HSLAPixel &pixel = getPixel(w, h);
            pixel.l += amount;
            if (pixel.l > 1)
                pixel.l = 1;
        }
    }
};
void Image::rotateColor(double agrees)
{
    for (unsigned int w = 0; w < width(); w++)
    {
        for (unsigned int h = 0; h < height(); h++)
        {
            cs225::HSLAPixel &pixel = getPixel(w, h);
            pixel.h += agrees;
            if (pixel.h > 360)
                pixel.h -= 360;
            if (pixel.h < 0)
                pixel.h += 360;
        }
    }
};
void Image::saturate()
{
    for (unsigned int w = 0; w < width(); w++)
    {
        for (unsigned int h = 0; h < height(); h++)
        {
            cs225::HSLAPixel &pixel = getPixel(w, h);
            pixel.s += 0.1;
            if (pixel.s > 1)
                pixel.s = 1;
        }
    }
};
void Image::saturate(double amount)
{
    for (unsigned int w = 0; w < width(); w++)
    {
        for (unsigned int h = 0; h < height(); h++)
        {
            cs225::HSLAPixel &pixel = getPixel(w, h);
            pixel.s += amount;
            if (pixel.s > 1)
                pixel.s = 1;
        }
    }
};
void Image::scale(double factor)
{
    Image oriImage = *this;
    resize(width() * factor, height() * factor);
    for (unsigned int w = 0; w < width(); w++)
    {
        for (unsigned int h = 0; h < height(); h++)
        {
            this->getPixel(w, h) = oriImage.getPixel(w / factor, h / factor);
        }
    }
};
void Image::scale(unsigned ww, unsigned hh)
{
    Image oriImage = *this;
    double w_ratio, h_ratio;
    double www = ww;
    double hhh = hh;
    w_ratio = www / width();
    h_ratio = hhh / height();
    resize(ww, hh);
    for (unsigned int w = 0; w < ww; w++)
    {
        for (unsigned int h = 0; h < hh; h++)
        {
            this->getPixel(w, h) = oriImage.getPixel(w / w_ratio, h / h_ratio);
        }
    }
};