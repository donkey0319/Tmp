/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>

using namespace std;

class StickerSheet
{
public:
    StickerSheet();
    StickerSheet(const Image &picture, unsigned max);
    StickerSheet(const StickerSheet &other);
    ~StickerSheet();
    const StickerSheet &operator=(const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, int x, int y);
    int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
    bool translate(unsigned index, int x, int y);
    void removeSticker(unsigned index);
    int layers() const;
    Image render() const;
    Image *getSticker(unsigned index);

private:
    Image _baseImage;

    unsigned int _max, _size;
    vector<Image *> _images;
    vector<int> _xCoor, _yCoor;
};