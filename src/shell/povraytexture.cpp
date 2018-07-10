#include "povraytexture.hpp"
void POVRayTexture::setPigment(POVRayColor color)
{
    pigment = "color " + POVRayColorMap[static_cast<int>(color)];
}

void POVRayTexture::setPigment(int colorID)
{
    pigment = "color " + POVRayColorMap[static_cast<int>(static_cast<POVRayColor>(colorID))];
}

void POVRayTexture::setPigment(POVRayPattern pattern)
{
    pigment = POVRayPatternMap[static_cast<int>(pattern)];
}

void POVRayTexture::setPigment(LibGeoDecomp::Coord<3> RGB, double transparensy)
{
    setPigment(LibGeoDecomp::FloatCoord<3>(RGB) / 256, transparensy);
}

void POVRayTexture::setPigment(LibGeoDecomp::FloatCoord<3> RGB, double transparensy)
{
    for (int i = 0; i < 3; ++i) {
        if (RGB[i] < 0)
            RGB[i] = 0;
        else if (RGB[i] > 1)
            RGB[i] = 1;
    }

    if (transparensy < 0)
        transparensy = 0;
    else if (transparensy > 1)
        transparensy = 1;


    pigment = "color rgbf<" + std::to_string(RGB[0]), +"," + std::to_string(RGB[1]), +","
        + std::to_string(RGB[2]), +">";
}

void POVRayTexture::setManually(const std::string &texture)
{
    manual = true;
    manualTexture = texture;
}

static const std::string POVRayColorMapData[] = {
    "Black",
    "White",
    "Red",
    "Green",
    "Blue",
    "Yellow",
    "Cyan",
    "Magenta",
    "",
    "Aquamarine",
    "BlueViolet",
    "Brown",
    "CadetBlue",
    "Coral",
    "CornflowerBlue",
    "DarkGreen",
    "DarkOliveGreen",
    "DarkOrchid",
    "DarkSlateBlue",
    "DarkSlateGray",
    "DarkTurquoise",
    "Firebrick",
    "ForestGreen",
    "Gold",
    "Goldenrod",
    "GreenYellow",
    "IndianRed",
    "Khaki",
    "LightBlue",
    "LightSteelBlue",
    "LimeGreen",
    "Maroon",
    "MediumAquamarine",
    "MediumBlue",
    "MediumForestGreen",
    "MediumGoldenrod",
    "MediumOrchid",
    "MediumSeaGreen",
    "MediumSlateBlue",
    "MediumSpringGreen",
    "MediumTurquoise",
    "MediumVioletRed",
    "MidnightBlue",
    "Navy",
    "NavyBlue",
    "Orange",
    "OrangeRed",
    "Orchid",
    "PaleGreen",
    "Pink",
    "Plum",
    "Salmon",
    "SeaGreen",
    "Sienna",
    "SkyBlue",
    "SlateBlue",
    "SpringGreen",
    "SteelBlue",
    "Tan",
    "Thistle",
    "Turquoise",
    "Violet",
    "VioletRed",
    "Wheat",
    "YellowGreen",
    "SummerSky",
    "RichBlue",
    "Brass",
    "Copper",
    "Bronze",
    "Bronze2",
    "Silver",
    "BrightGold",
    "OldGold",
    "Feldspar",
    "Quartz",
    "NeonPink",
    "DarkPurple",
    "NeonBlue",
    "CoolCopper",
    "MandarinOrange",
    "LightWood",
    "MediumWood",
    "DarkWood",
    "SpicyPink",
    "SemiSweetChoc",
    "BakersChoc",
    "Flesh",
    "NewTan",
    "NewMidnightBlue",
    "",
    "VeryDarkBrown",
    "DarkBrown",
    "GreenCopper",
    "DkGreenCopper",
    "DustyRose",
    "HuntersGreen",
    "Scarlet",
    "DarkTan"
};

static const std::string POVRayPatternMapData[] = {
    "Jade",
    "Red_Marble",
    "White_Marble",
    "Blood_Marble",
    "Blue_Agate",
    "Sapphire_Agate",
    "Brown_Agate",
    "Pink_Granite",
    "Candy_Cane",
    "Y_Gradient",
    "X_Gradient",
    "Cork",
    "Cherry_Wood",
    "Pine_Wood",
    "Dark_Wood",
    "Tan_Wood",
    "White_Wood",
    "Tom_Wood",
    "DMFWood1",
    "DMFWood2",
    "DMFWood3",
    "DMFWood4",
    "DMFWood5",
    "DMFLightOak",
    "DMFDarkOak",
    "Blue_Sky",
    "Bright_Blue_Sky",
    "Blue_Sky2",
    "Blue_Sky3",
    "Blood_Sky",
    "Apocalypse",
    "Clouds",
    "FBM_Clouds"
};

const std::string *POVRayTexture::POVRayColorMap = POVRayColorMapData;

const std::string *POVRayTexture::POVRayPatternMap = POVRayPatternMapData;

std::ostream &operator<<(std::ostream &os, const POVRayTexture &povrayTexture)
{
    if (!povrayTexture.manual) {
        os << "    pigment{\n      " << povrayTexture.pigment << "\n    }\n";
        if (!povrayTexture.normal.empty())
            os << "    normal{\n      " << povrayTexture.normal << "\n    }\n";
        os << "    finish{\n      " << povrayTexture.finish << "\n    }\n";
    }
    else
        os << povrayTexture.manualTexture;
    return os;
}
void POVRayTexture::setNormal(const std::string &normal)
{
    POVRayTexture::normal = normal;
}
void POVRayTexture::setFinish(const std::string &finish)
{
    POVRayTexture::finish = finish;
}
POVRayTexture::POVRayTexture(const std::string &pigment, const std::string &normal, const std::string &finish)
    : pigment(pigment), normal(normal), finish(finish)
{

}
POVRayTexture::POVRayTexture(const POVRayTexture &other)
    :pigment(other.pigment), normal(other.normal), finish(other.finish)
{
}
