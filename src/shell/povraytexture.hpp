#ifndef NEWTONIAN_PHYSICS_SANDBOX_POVRAYTEXTURE_HPP
#define NEWTONIAN_PHYSICS_SANDBOX_POVRAYTEXTURE_HPP

#include <libgeodecomp/geometry/coord.h>
#include <libgeodecomp/geometry/floatcoord.h>
namespace
{
enum class POVRayPigment
{
    COLOR,
    RGBCOLOR,
    RGBF,
    COLORPATTERN
};
}
enum class POVRayColor
{
    Black = 0,
    White,
    Red,
    Green,
    Blue,
    Yellow,
    Cyan,
    Magenta,
    Aquamarine = 9,
    BlueViolet,
    Brown,
    CadetBlue,
    Coral,
    CornflowerBlue,
    DarkGreen,
    DarkOliveGreen,
    DarkOrchid,
    DarkSlateBlue,
    DarkSlateGray,
    DarkTurquoise,
    Firebrick,
    ForestGreen,
    Gold,
    Goldenrod,
    GreenYellow,
    IndianRed,
    Khaki,
    LightBlue,
    LightSteelBlue,
    LimeGreen,
    Maroon,
    MediumAquamarine,
    MediumBlue,
    MediumForestGreen,
    MediumGoldenrod,
    MediumOrchid,
    MediumSeaGreen,
    MediumSlateBlue,
    MediumSpringGreen,
    MediumTurquoise,
    MediumVioletRed,
    MidnightBlue,
    Navy,
    NavyBlue,
    Orange,
    OrangeRed,
    Orchid,
    PaleGreen,
    Pink,
    Plum,
    Salmon,
    SeaGreen,
    Sienna,
    SkyBlue,
    SlateBlue,
    SpringGreen,
    SteelBlue,
    Tan,
    Thistle,
    Turquoise,
    Violet,
    VioletRed,
    Wheat,
    YellowGreen,
    SummerSky,
    RichBlue,
    Brass,
    Copper,
    Bronze,
    Bronze2,
    Silver,
    BrightGold,
    OldGold,
    Feldspar,
    Quartz,
    NeonPink,
    DarkPurple,
    NeonBlue,
    CoolCopper,
    MandarinOrange,
    LightWood,
    MediumWood,
    DarkWood,
    SpicyPink,
    SemiSweetChoc,
    BakersChoc,
    Flesh,
    NewTan,
    NewMidnightBlue,
    VeryDarkBrown = 91,
    DarkBrown,
    GreenCopper,
    DkGreenCopper,
    DustyRose,
    HuntersGreen,
    Scarlet,
    DarkTan,
};

enum class POVRayPattern
{
    Jade,
    Red_Marble,
    White_Marble,
    Blood_Marble,
    Blue_Agate,
    Sapphire_Agate,
    Brown_Agate,
    Pink_Granite,
    Candy_Cane,
    Y_Gradient,
    X_Gradient,
    Cork,
    Cherry_Wood,
    Pine_Wood,
    Dark_Wood,
    Tan_Wood,
    White_Wood,
    Tom_Wood,
    DMFWood1,
    DMFWood2,
    DMFWood3,
    DMFWood4,
    DMFWood5,
    DMFLightOak,
    DMFDarkOak,
    Blue_Sky,
    Bright_Blue_Sky,
    Blue_Sky2,
    Blue_Sky3,
    Blood_Sky,
    Apocalypse,
    Clouds,
    FBM_Clouds
};

class POVRayNORMAL_IDENTIFIER
{
//TODO
};

class POVRayNORMAL_TYPE
{
//TODO
};

class POVRayNORMAL_MODIFIERS
{
//TODO
};

class POVRayTexture
{
public:
    POVRayTexture(const std::string &pigment = "color White",
                  const std::string &normal = "",
                  const std::string &finish = "phong 0.9 metallic");
    POVRayTexture(const POVRayTexture& other);
    void setPigment(int);
    void setPigment(POVRayColor);
    void setPigment(POVRayPattern);
    void setPigment(LibGeoDecomp::Coord<3>, double transparensy = 1);
    void setPigment(LibGeoDecomp::FloatCoord<3>, double transparensy = 1);
    void setManually(const std::string &);

    void setNormal(const std::string &);
    //TODO
    void setNormal(POVRayNORMAL_IDENTIFIER, POVRayNORMAL_TYPE, POVRayNORMAL_MODIFIERS);

    void setFinish(const std::string &);
    friend std::ostream &operator<<(std::ostream &, const POVRayTexture &);
private:
    bool manual = false;
    std::string manualTexture;
    static const std::string* POVRayColorMap;
    static const std::string* POVRayPatternMap;
    std::string pigment;
    std::string normal;
    std::string finish;
};

#endif //NEWTONIAN_PHYSICS_SANDBOX_POVRAYTEXTURE_HPP
