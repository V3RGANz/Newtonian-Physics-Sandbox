#include "npsimporter.hpp"

namespace
{
inline std::vector<std::string> tokenizer(const std::string &sentence)
{
    std::istringstream iss(sentence);
    return {std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}};
}

inline void getRidOfNormals(std::vector<std::string> &tokens)
{
    std::cout << "\n";
    for (auto &str : tokens) {
        auto pos = str.find("//");
        if (pos != std::string::npos)
            str.erase(pos, std::string::npos);
    }
}
}

/**
 * Load scene from .obj file. Ignores all except spheres
 * @param filepath path to .obj file
 */
void SimpleOBJSpheresImporter::import(std::string filepath)
{
    std::cout << "SimpleOBJSpheresImporter::import" << std::endl;
    std::ifstream scene(filepath);
    if (scene) {
        // TODO: error handling
    }

    std::string currentLine;

    while (true) {
        if (!getline(scene, currentLine)) {
            std::cout << "EOF\n";
            return;
        }
        std::cout << "got line " << currentLine << std::endl;
        if (currentLine.find("Mball") != std::string::npos) {
            std::cout << "currentLine.find(\"Mball\") != std::string::npos" << std::endl;
            break;
        }
    }

    std::vector<FloatCoord<3>> vertices;
    std::vector<std::string> LineTokens;

    while (true) {
        if (!getline(scene, currentLine)) {
            std::cout << "EOF\n";
            return;
        }
        std::cout << "got line " << currentLine << std::endl;
        LineTokens = tokenizer(currentLine);

        std::cout << "tokens: ";

        for (auto token : LineTokens){
            std::cout << token << " ";
        }

        std::cout << std::endl;

        if (!LineTokens.empty()){
            if (!LineTokens[0].empty()) {
                if (LineTokens[0][0] == '#')
                    continue;
            }
            else
                continue;
        }
        if (LineTokens.size() > 3) {
            if (LineTokens[0] != "v")
                break;
        }
        else
            break;
        vertices.emplace_back(::strtod(LineTokens[1].c_str(), nullptr),
                              ::strtod(LineTokens[2].c_str(), nullptr),
                              ::strtod(LineTokens[3].c_str(), nullptr));

        std::cout << "vertex read: " << vertices.back() << std::endl;
    }
    std::cout << "vertices.size(): " << vertices.size() << std::endl;

    while (true) {
        if (!LineTokens.empty()) {
            if (LineTokens[0] == "f")
                break;
        }

        if (!getline(scene, currentLine))
            return;
        LineTokens = tokenizer(currentLine);
    }

    std::map<FloatCoord<3>, int> vertexSets;
    std::map<int, std::set<FloatCoord<3> > > setNumbers;
    int setNumber = 0;
    std::cout << "face found: " << std::endl;

    while (true) {
        getRidOfNormals(LineTokens);
        std::cout << "got Rid Of Normals" << std::endl;

        for (auto token : LineTokens)
            std::cout << token << " ";
        std::cout << "\n";

        std::set<int> foundSets;
        std::set<FloatCoord<3> > unnamedVertices;

        for (int i = 1; i < LineTokens.size(); ++i) {
            int vertexNumber = ::atoi(LineTokens[i].c_str());
            auto found = vertexSets.find(vertices[vertexNumber]);
            if (found != vertexSets.end()) {
                foundSets.insert(found->second);
            }
            else {
                unnamedVertices.insert(vertices[vertexNumber]);
            }
        }
        if (!foundSets.empty()) {
            int maxid = *foundSets.begin();
            std::size_t maxsize = setNumbers[maxid].size();
            for (int curSet: foundSets) {
                std::size_t curSize = setNumbers[curSet].size();
                if (curSize > maxsize) {
                    maxid = curSet;
                    maxsize = curSize;
                }
            }
            foundSets.erase(maxid);
            auto &maxset = setNumbers[maxid];
            for (int curSet: foundSets) {
                auto found = setNumbers.find(curSet);
                maxset.insert(found->second.begin(), found->second.end());
                for (auto vertex : found->second) {
                    vertexSets[vertex] = maxid;
                }
                setNumbers.erase(found);
            }
            maxset.insert(unnamedVertices.begin(), unnamedVertices.end());
            for (auto vertex : unnamedVertices) {
                vertexSets[vertex] = maxid;
            }
        }
        else {
            setNumbers.insert(std::pair<int, std::set<FloatCoord<3> > >(setNumber, unnamedVertices));
            for (auto vertex : unnamedVertices) {
                vertexSets[vertex] = setNumber;
            }
            ++setNumber;
        }
        if (LineTokens.size() > 3) {
            if (LineTokens[0] != "f") {
                break;
            }
        }
        else {
            break;
        }
        if (!getline(scene, currentLine))
            break;
        LineTokens = tokenizer(currentLine);
    }

    for (auto setPair : setNumbers) {
        auto curSet = setPair.second;
        FloatCoord<3> position = FloatCoord<3>(0);
        for (auto vertex : curSet){
            position += vertex;
        }
        position /= curSet.size();
        double radius = (position - *curSet.begin()).length();
        importedObjects.push_back(ComposedSpheresCB({{position, radius}}));
    }
}
std::list<ComposedSpheresCB> SimpleOBJSpheresImporter::getObjects()
{
    return importedObjects;
}
