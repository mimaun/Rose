#ifndef __IMAGE_BUILDER
#define __IMAGE_BUILDER

#define RES 100

class ImageBuilder
{
public:
    void setup(std::vector<Colorer*> & imageColorers)
    {
        //TODO 1 : replace the body of this method with whatever you like
        //         you may not change the method signature
        
        for(size_t i=0; i<imageColorers.size(); i++) {

            // fill with NoiseColor
            imageColorers.at(i) = new NoiseColor();

            // horizon line && alpha filter
            if(i < imageColorers.size() * 2/3 && i > imageColorers.size()/3 && i % 3 == 0) {
                imageColorers.at(i) = new WhiteColorer();
            }

            // stairs
            if(i % 70 < 7) {
                imageColorers.at(i) = new WhiteColorer();
            }
        } 
    }
    
    void color(std::vector<Colorer*> const & imageColorers, std::vector<rgb> & rgbColors)
    {
        bool sizesMatch = imageColorers.size() == rgbColors.size();
        bool hasPixels = rgbColors.size() > 0;
        assert(sizesMatch);
        assert(hasPixels);
        
        for(size_t i=0; i<rgbColors.size(); i++)
            imageColorers.at(i)->colorPixel( rgbColors.at(i) );
    }
};

#endif
