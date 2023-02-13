// hi
#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max)
{
    _baseImage = Image(picture);
    _max = max;
    _size = 0;
    for (unsigned i = 0; i < _max; i++)
    {
        _images.push_back(NULL);
    }
};
StickerSheet::StickerSheet(const StickerSheet &other)
{
    _baseImage = Image(other._baseImage);
    _max = other._max;
    _size = other._size;

    for (unsigned int i = 0; i < _max; i++)
    {
        _images.push_back(other._images[i]);
    }
    for (unsigned int j = 0; j < _size; j++)
    {
        _xCoor.push_back(other._xCoor[j]);
        _yCoor.push_back(other._yCoor[j]);
    }
};
const StickerSheet &StickerSheet::operator=(const StickerSheet &other)
{
    if (this == &other)
        return *this;

    _baseImage = Image(other._baseImage);
    _max = other._max;
    _size = other._size;

    for (unsigned int i = 0; i < _size; i++)
    {
        _images.push_back(new Image(*(other._images[i])));
    }
    for (unsigned int i = _size; i < _max; i++)
    {
        _images.push_back(NULL);
    }
    for (unsigned int j = 0; j < _size; j++)
    {
        _xCoor.push_back(other._xCoor[j]);
        _yCoor.push_back(other._yCoor[j]);
    }

    return *this;
};
StickerSheet::~StickerSheet()
{
    _images.clear();
};

void StickerSheet::changeMaxStickers(unsigned max)
{
    if (_max < max)
    {
        for (size_t i = _max; i < max; i++)
        {
            _images.push_back(NULL);
        }
    }
    else if (max < _size)
    {
        _size = max;
    }
    _max = max;
};
int StickerSheet::addSticker(Image &sticker, int x, int y)
{
    if (_size >= _max)
    {
        _max = _size + 1;
        _images.push_back(&sticker);
    }
    else
    {
        _images[_size] = &sticker;
    }
    _size += 1;
    _xCoor.push_back(x);
    _yCoor.push_back(y);

    return _size - 1;
};
int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y)
{
    if (layer >= _size)
        return -1;
    _images[layer] = &sticker;
    _xCoor[layer] = x;
    _yCoor[layer] = y;
    return layer;
    // !!!!!!!!!!!!!!!!
};
bool StickerSheet::translate(unsigned index, int x, int y)
{
    if (_size <= index)
        return false;
    _xCoor[index] = x;
    _yCoor[index] = y;
    return true;
}
void StickerSheet::removeSticker(unsigned index)
{
    _images.erase(_images.begin() + index);
    _xCoor.erase(_xCoor.begin() + index);
    _yCoor.erase(_yCoor.begin() + index);
    _size -= 1;
    _images.push_back(NULL);

    // !!!!!!!!!!!
};
int StickerSheet::layers() const
{
    return _max;
};
Image StickerSheet::render() const
{
    if (_images[0] == NULL)
    {
        return _baseImage;
    }

    // Step 1: Find w and h
    int nx = 0;
    int ny = 0;
    for (unsigned i = 0; i < _size; i++)
    {
        if (_xCoor[i] < nx)
            nx = _xCoor[i];
        if (_yCoor[i] < ny)
            ny = _yCoor[i];
    }

    unsigned px = _baseImage.width();
    unsigned py = _baseImage.height();
    for (size_t i = 0; i < _size; i++)
    {
        if (_xCoor[i] + _images[i]->width() > px)
            px = _xCoor[i] + _images[i]->width();
        if (_yCoor[i] + _images[i]->height() > py)
            py = _yCoor[i] + _images[i]->height();
    }

    // Step 2: Image img(w, h)
    Image img(unsigned(-nx + px), unsigned(-ny + py));

    // Step 3: Insert base image at nx ny
    for (size_t x = 0; x < _baseImage.width(); x++)
    {
        for (size_t y = 0; y < _baseImage.height(); y++)
        {
            // cout << "access base image" << endl;
            // cout << "access canvas" << endl;
            img.getPixel(x - nx, y - ny) = _baseImage.getPixel(x, y);
        }
    }

    // Step 4: Insert each sticker
    for (size_t i = 0; i < _size; i++) // iterating over every sticker
    {
        for (size_t w = 0; w < _images[i]->width(); w++)
        {
            for (size_t h = 0; h < _images[i]->height(); h++)
            {
                if (_images[i]->getPixel(w, h).a != 0)
                {
                    img.getPixel(w + _xCoor[i] - nx, h + _yCoor[i] - ny) = _images[i]->getPixel(w, h);
                }
            }
        }
    }
    return img;
}
Image *StickerSheet::getSticker(unsigned index)
{
    if (index >= _size)
        return NULL;
    return _images[index];
};