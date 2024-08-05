#include<iostream>
#include<fstream>
#include<filesystem>
#include <sstream>
#include<windows.h>
#include <shlobj.h>
#include<vector>
#include <cstdlib>
#include <sstream>
#include <map>
#include <set>
#include <utility>
#include <cmath>
#include <random>
//#include <algorithm>
struct TGAHeader {
    uint8_t idLength = 0;
    uint8_t colorMapType = 0;
    uint8_t imageType = 2; // Uncompressed True-color image
    uint8_t colorMapSpec[5] = {0};
    uint16_t xOrigin = 0;
    uint16_t yOrigin = 0;
    uint16_t width;
    uint16_t height;
    uint8_t pixelDepth = 32;
    uint8_t imageDescriptor = 0x20; // Top-left origin
};

void writeTGA(const std::string& filename, uint16_t width, uint16_t height, const std::vector<std::tuple<uint8_t,uint8_t,uint8_t,uint8_t>>& imageData) {
    TGAHeader header;
    header.width = width;
    header.height = height;

    std::ofstream file(filename, std::ios::binary);
    /*if (!file) {
        std::cerr << "Error: Unable to open file for writing.\n";
        return;
    }*/

    // Write the TGA header
    file.write(reinterpret_cast<const char*>(&header), sizeof(header));

    // Write the image data
    file.write(reinterpret_cast<const char*>(imageData.data()), imageData.size()*4);

    file.close();
    //std::cout << "TGA file created successfully: " << filename << "\n";
}
#pragma pack(push, 1) // Ensure no padding between structure fields

struct BMPFileHeader {
    uint16_t fileType{0x4D42}; 
    uint32_t fileSize{0};      
    uint16_t reserved1{0};     
    uint16_t reserved2{0};     
    uint32_t offsetData{54};   
};
struct BMPInfoHeader {
    uint32_t size{40};         
    int32_t width{0};          
    int32_t height{0};         
    uint16_t planes{1};        
    uint16_t bitCount{24};     
    uint32_t compression{0};   
    uint32_t sizeImage{0};     
    int32_t xPixelsPerMeter{0};
    int32_t yPixelsPerMeter{0};
    uint32_t colorsUsed{0};    
    uint32_t colorsImportant{0};
};
#pragma pack(pop)
int printNum = 1;
int start = GetTickCount();
struct stateInterface;
void print(){std::cout<<printNum++<<" "<<(GetTickCount()-start)/1000.<<"|test"<<"\n";}
void print(std::string input){std::cout<<printNum++<<" "<<(GetTickCount()-start)/1000.<<"|"<<input<<"\n";}
void print(int input){std::cout<<printNum++<<" "<<(GetTickCount()-start)/1000.<<"|"<<input<<"\n";}
void print(int input,int in){std::cout<<printNum++<<" "<<(GetTickCount()-start)/1000.<<"|"<<input<<" "<<in<<"\n";}
void print(double input){std::cout<<printNum++<<" "<<(GetTickCount()-start)/1000.<<"|"<<input<<"\n";}
int randomNum(int min, int max) {
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(min, max); // Define the range

    return distr(gen); // Generate the number
}

std::vector<std::string> split(std::string &str,std::string delim){
	std::vector<std::string> rez;
	int wher = 0;
	int prev = 0;
	while(wher != -1){
		wher = str.find(delim,wher+1);
		rez.push_back(str.substr(prev,wher-prev));
		prev = wher+1;
	}
	return rez;
}
std::string between(std::string line,std::string str){
	int start = line.find(str);
	int end = line.find(str, start + 1);
	return line.substr(start + 1, end - start - 1);
};
std::string between(std::string line,std::string str,std::string str2){
	int start = line.find(str);
	int end = line.find(str2, start + 1);
	return line.substr(start + 1, end - start - 1);
};
std::string join(std::vector<std::string> &str){
    std::string rez;
	for( auto i: str){
	    rez+=i;
	}
	return rez;
}
std::ofstream copy_file(std::string a,std::string b){
    std::ifstream  src(a, std::ios::binary);
    std::ofstream  dst(b, std::ios::binary);
    dst << src.rdbuf();src.close();dst.close();
	dst.close();src.close();
    return std::ofstream(b, std::ios_base::app);
}
std::ofstream newFile(std::string path,std::string text = "nO tExt"){
    std::filesystem::create_directories(path.substr(0, path.find_last_of('/')));
	std::ofstream failas = std::ofstream(path);
	if(text != "nO tExt"){
		failas<<text;
		failas.close();
	}
    return failas;
};
bool isUpper(char character){
    return (character>='A'&&character<='Z');
};
void print(std::pair<std::tuple<uint8_t, uint8_t, uint8_t>,int> input){std::cout<<printNum++<<"|"<<
int(std::get<0>(input.first))<<" "<<int(std::get<1>(input.first))<<" "<<int(std::get<2>(input.first))<<" "<<input.second<<"\n";}
void print(std::tuple<uint8_t, uint8_t, uint8_t> input){std::cout<<printNum++<<"|"<<
int(std::get<0>(input))<<" "<<int(std::get<1>(input))<<" "<<int(std::get<2>(input))<<"\n";}
std::tuple<uint8_t,uint8_t,uint8_t> randomColor(){
	return std::make_tuple((std::rand() % 256),(std::rand() % 256),(std::rand() % 256));
}
struct BMPImage {
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
	std::ofstream file;
    std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> pixels;
	void setSize(int w,int h){
		infoHeader.width = w;
		infoHeader.height = h;
	}
	void openFile(std::string name = "test.bmp"){
		file.open(name,std::ios::binary);;
	}
	~BMPImage(){
		file.close();
	}
};
void readbmp(const std::string& filename, BMPImage& image, std::map<std::tuple<uint8_t, uint8_t, uint8_t>,int>& pixels) {
    std::ifstream file(filename, std::ios::binary);
    file.read(reinterpret_cast<char*>(&image.fileHeader), sizeof(image.fileHeader));
    file.read(reinterpret_cast<char*>(&image.infoHeader), sizeof(image.infoHeader));

    // Check if input image is 24-bit BMP
    if (image.infoHeader.bitCount != 24) {
        std::cerr << "Error: Input image must be a 24-bit BMP." << std::endl;
    }

    // Calculate row stride
    int rowStride = (image.infoHeader.width * 3 + 3) & ~3; // Align to 4-byte boundary

    // Move file pointer to the beginning of pixel data
    file.seekg(image.fileHeader.offsetData, std::ios::beg);

    // Read pixel data
    image.pixels.resize(image.infoHeader.width * image.infoHeader.height);
    std::vector<uint8_t> row(rowStride);
    for (int y = 0; y < image.infoHeader.height; ++y) {
        file.read(reinterpret_cast<char*>(row.data()), rowStride);
        for (int x = 0; x < image.infoHeader.width; ++x) {
            int pixelIndex = (image.infoHeader.height - 1 - y) * image.infoHeader.width + x;
			std::tuple<uint8_t, uint8_t, uint8_t> pixelis = std::make_tuple(row[x * 3+2],row[x * 3 + 1],row[x * 3]);
            image.pixels[pixelIndex] = pixelis;
			pixels[pixelis]++;
        }
    }
}
void readbmpNoMap(const std::string& filename, BMPImage& image) {
    std::ifstream file(filename, std::ios::binary);
    file.read(reinterpret_cast<char*>(&image.fileHeader), sizeof(image.fileHeader));
    file.read(reinterpret_cast<char*>(&image.infoHeader), sizeof(image.infoHeader));

    // Check if input image is 24-bit BMP
    if (image.infoHeader.bitCount != 24) {
        std::cerr << "Error: Input image must be a 24-bit BMP." << std::endl;
    }

    // Calculate row stride
    int rowStride = (image.infoHeader.width * 3 + 3) & ~3; // Align to 4-byte boundary

    // Move file pointer to the beginning of pixel data
    file.seekg(image.fileHeader.offsetData, std::ios::beg);

    // Read pixel data
    image.pixels.resize(image.infoHeader.width * image.infoHeader.height);
    std::vector<uint8_t> row(rowStride);
	//print(image.infoHeader.width);
    for (int y = 0; y < image.infoHeader.height; ++y) {
		//print(0);
        file.read(reinterpret_cast<char*>(row.data()), rowStride);
        for (int x = 0; x < image.infoHeader.width; ++x) {
			//print(0);
            int pixelIndex = y*image.infoHeader.width+x;//(image.infoHeader.height - 1 - y) * image.infoHeader.width + x;
			//print((image.infoHeader.height - 1 - y) * image.infoHeader.width + x);
			std::tuple<uint8_t, uint8_t, uint8_t> pixelis = std::make_tuple(row[x * 3+2],row[x * 3 + 1],row[x * 3]);
            image.pixels[pixelIndex] = pixelis;
			//pixels[pixelis]++;
        }
    }
}
struct Dot {
    int x;
    int y;
    std::tuple<uint8_t, uint8_t, uint8_t> color;
};
double distance(int x1, int y1, int x2, int y2) {
	double dx = std::abs(x1 - x2);
    double dy = std::abs(y1 - y2);
    return (dx * dx * dx + dy * dy * dy);
}
void createBMP(int width, int height, BMPImage& image,bool finished,std::string where,
std::tuple<uint8_t,uint8_t,uint8_t> color = std::make_tuple(0, 0, 0),std::string pltn = "n") {
	int bits = 24;
	if(pltn != "n")bits = 8;
	image.infoHeader.bitCount = bits;
    image.infoHeader.width = width;
    image.infoHeader.height = height;

    int rowStride = (width * 3 + 3) & ~3; // Align to 4-byte boundary
	if(pltn != "n")rowStride = width;
    image.infoHeader.sizeImage = rowStride * height;
    image.fileHeader.fileSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + image.infoHeader.sizeImage;

	image.openFile(where);

    // Write headers
	if(image.infoHeader.bitCount == 8)image.fileHeader.offsetData = 54 + 256 * 4;
    image.file.write(reinterpret_cast<const char*>(&(image.fileHeader)), sizeof(image.fileHeader));
    image.file.write(reinterpret_cast<const char*>(&(image.infoHeader)), sizeof(image.infoHeader));
	uint8_t colorPalette[1024];  // 256 colors * 4 bytes each (RGBA)
	
	if(pltn != "n"){
		std::ifstream brofile = std::ifstream("hoi4-data/palettes/"+pltn+".palettetxt");
		std::string line;
		std::getline(brofile, line);
		for (int i = 0; i < 256; ++i) {
			if(std::getline(brofile, line)){
			auto colors = split(line,",");//b r g
			colorPalette[i * 4] = std::stoi(colors[0]);   // Red
			colorPalette[i * 4 + 1] = std::stoi(colors[1]); // Green
			colorPalette[i * 4 + 2] = std::stoi(colors[2]); // Blue
			colorPalette[i * 4 + 3] = std::stoi(colors[3]); // Reserved (Alpha)
			}
		}
		image.file.write(reinterpret_cast<char*>(&colorPalette), sizeof(colorPalette));
	}
    // Write pixel data (red color)
	
	if(finished){
		if(pltn != "n"){std::vector<uint8_t> row(rowStride*height,std::get<0>(color));
		image.file.write(reinterpret_cast<const char*>(row.data()), rowStride*height);}
		else{std::vector<std::tuple<uint8_t,uint8_t,uint8_t>> row(rowStride*height,color);
		image.file.write(reinterpret_cast<const char*>(row.data()), rowStride*height);}
		//image.file.write(reinterpret_cast<const char*>(row.data()), rowStride*height);
		image.file.close();
	}
    //std::cout << "BMP file created successfully: " << filename << std::endl;
}
void generateRandomProvincesOntoBMP(BMPImage& image, int averageProvinceSize,int chunksize);
void countriesMapIntoStates(BMPImage& image, int averageProvinceSize, int chunksize,int proVaverageProvinceSize,int proVchunksize);
void deleteBlackBorder(BMPImage& image);
void finishImage(BMPImage& image,std::string where,bool headers = true);
void landNSeaHeightSeperation(BMPImage& provinces,BMPImage& height,BMPImage& terrain);
void findCoastals(BMPImage& provinces);
void makeStrategicRegions(BMPImage& image);
/*
void editbmp(const std::string& filename) {
    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    if (infoHeader.bitCount != 24) {
        std::cerr << "Error: Input image must be a 24-bit BMP." << std::endl;
        return;
    }
    int rowStride = (infoHeader.width * 3 + 3) & ~3;
    file.seekp(fileHeader.offsetData, std::ios::beg);
    std::vector<uint8_t> row(rowStride);
    for (int y = 0; y < infoHeader.height; ++y) {
        file.read(reinterpret_cast<char*>(row.data()), rowStride);
        for (int x = 0; x < infoHeader.width; x+=3) {
            row[x] = 0xFF;
            row[x+1] = 0;
            row[x+2] = 0;
        }
        file.seekp(-rowStride, std::ios::cur);
        file.write(reinterpret_cast<const char*>(row.data()), rowStride);
    }
}*/
//----INTERFACES----INTERFACES----INTERFACES----INTERFACES----INTERFACES----INTERFACES
struct modClass{
	std::set<std::string> tags;//not country tags
	std::vector<std::string> replace;
	std::string gameVersion = "1.14.*";
	int timesbuilt = 1;
	void addTag(std::string tag){
		tags.insert(tag);
	}
	modClass(){
		std::filesystem::remove_all("src");
		std::filesystem::create_directories("src");
	}
	void makeDescriptor(bool outsider = false){
		std::ofstream descriptor;
		if (outsider) {
			CHAR my_documents[MAX_PATH];
			HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);
			std::string documentsPath(my_documents);
			documentsPath += "\\Paradox Interactive\\Hearts of Iron IV\\mod\\generatedMapModDescriptor.mod";
			//print(documentsPath);
			descriptor.open(documentsPath);
		} else {
			descriptor.open("src/descriptor.mod");
		}
		descriptor<<"tags={\n";
		for(std::string i : tags){
			descriptor<<"\t\""<<i<<"\"\n";
		}
		descriptor<<"}\n";
		descriptor<<"name=\"Generated Map Mod\"\n";
		descriptor<<"picture=\"thumbnail.png\"\n";
		descriptor<<"version=\"test"<<timesbuilt<<"\"\n";
		for(std::string i : replace){
			descriptor<<"replace_path=\""<<i<<"\"\n";
		}
		descriptor<<"supported_version=\""<<gameVersion<<"\"";
		if(outsider){
			char path[MAX_PATH];
			GetModuleFileNameA(NULL, path, MAX_PATH);
			for (char& c : path) {//stupid windows slashes
				if (c == '\\') {
					c = '/';
				}
			}
			std::string realPath = std::string(path);
			std::string folderPath;
			auto pathChunks = split(realPath,"/");
			for(int i = 0;i<pathChunks.size()-1;i++){
				folderPath += pathChunks[i]+"/";
			}
			descriptor<<"\npath=\""<<folderPath<<"src\"";
		}
		descriptor.close();
	}
    ~modClass(){
		//copy_file("hoi4-data/descriptor.mod", "src/descriptor.mod");
		if (std::filesystem::exists("builderdata")) {
			std::ifstream infile("builderdata");
			infile >> timesbuilt;
			infile.close();
		}
		std::ofstream outfile("builderdata");
		outfile << ++timesbuilt;
		outfile.close();
		makeDescriptor();
		makeDescriptor(true);
		copy_file("hoi4-data/thumbnail.png", "src/thumbnail.png");
		
		std::cout<<"SUCCESS, took "<<((GetTickCount()-start)/1000.)<<" seconds\n";//its over!
		int obfuscatedString[] = {104, 116, 116, 112, 115, 58, 47, 47, 103, 105, 116, 104, 117, 98, 46, 99, 111, 109, 47, 99, 111, 100, 105, 114, 101, 110, 47, 104, 111, 105, 52, 45, 109, 97, 112, 45, 103, 101, 110, 101, 114, 97, 116, 111, 114, 45, 102, 97, 115, 116, 45, 109, 97, 112, 112, 101, 114};
    size_t length = sizeof(obfuscatedString) / sizeof(obfuscatedString[0]);
    std::string sum;
    for (size_t i = 0; i < length; ++i) {
        sum += static_cast<char>(obfuscatedString[i]);
    }
    std::cout << sum << std::endl;
	}
};modClass mod;
struct focusInterface{
	int id;
	int length = 10;
	std::string searchFilter = "";
	std::string icon = "GFX_goal_unknown";
	std::string name;
	std::string desc;
	focusInterface(int newid){
		id = newid;
	}
};
struct eventInterface{
    std::string id;
    std::string title = "Breaking news";
    std::string desc = "Event description";
    std::string picture = "GFX_report_event_soviet_soldiers";
    std::string major = "yes";
    std::string trigger;
    std::vector<std::string> responseOptions;
};
struct localisationControllerClass{
    std::ofstream file;
    int localisationIdCounter = 1;
    localisationControllerClass(){
	std::filesystem::create_directories("src/localisation/english");
	file = copy_file("utf8 bom.yml", "src/localisation/english/translation_l_english.yml");
        file<<"l_english:";
    }
    ~localisationControllerClass(){
        file.close();
    }
    std::string addLocalization(std::string str,std::string nameSpace,int numbered = true){
        std::string tag = nameSpace;
		if(numbered)tag+="."+std::to_string(localisationIdCounter++);
        file<<"\n "<<tag<<":0 \""<<str<<"\"";
        return tag;
    }
};localisationControllerClass localisationController;
struct countryInterface{
    std::string name = "Agartha";
	std::string tag;
	std::string religion = "fascism";
	int red,green,blue;
	int capital = 1;
	std::ofstream focusTreeFile;
	int focusCounter = 1;
	int sizeInPixels = 0;
	std::vector<stateInterface*> states;
	std::pair<int,int> center;
	std::pair<std::pair<int,int>,std::pair<int,int>> frameBox;
	stateInterface* centerState;//not used
	void customFocusTree(){
		//std::ifstream file("hoi4-data/national_focus/generic.txt");
		//std::stringstream buffer;
		//buffer << file.rdbuf(); // Read the file's content into the buffer
		focusTreeFile = newFile("src/common/national_focus/"+tag+".txt");
		//focusTreeFile<<buffer.str();
		//file.close();
		focusTreeFile<<"focus_tree = {";
		focusTreeFile<<"\ndefault = no";
		focusTreeFile<<"\nid = focus_tree_"+tag;
		focusTreeFile<<"\ncountry = {";
		focusTreeFile<<"\nfactor = 0";
		focusTreeFile<<"\nmodifier = {";
		focusTreeFile<<"\n	add = 10";
		focusTreeFile<<"\n	tag = "+tag;
		focusTreeFile<<"\n}";
		focusTreeFile<<"\n}";
	}
	focusInterface* newFocus(){
		return new focusInterface(focusCounter++);
	}
	void addFocus(focusInterface* focus){
		focusTreeFile<<"\nfocus = {";
		focusTreeFile<<"\nid = focus_"+tag+"_"+std::to_string(focus->id);
		focusTreeFile<<"\nicon = "+focus->icon;//GFX_goal_generic_allies_build_infantry
		//focusTreeFile<<"prerequisite = { focus = army_effort }";//        unfinished
		focusTreeFile<<"\nx = 10";//1        unfinished
		focusTreeFile<<"\ny = 2";//0        unfinished
		focusTreeFile<<"\ncost = "+std::to_string(focus->length);
		if(focus->searchFilter!="")focusTreeFile<<"\nsearch_filters = { "+focus->searchFilter+" }";
		focusTreeFile<<"\ncompletion_reward = {";
		focusTreeFile<<"\n}}";
		localisationController.addLocalization(focus->name,"focus_"+tag+"_"+std::to_string(focus->id),false);
		localisationController.addLocalization(focus->desc,"focus_"+tag+"_"+std::to_string(focus->id)+"_desc",false);
	}
	~countryInterface(){
		focusTreeFile<<"\n}";
		focusTreeFile.close();
		//print("closed");
	}
};
struct provinceInterface{
    std::string name = "land";
	std::string terrain = "plains";
	std::string owner = "NAT";
	std::pair<int,int> center;
	bool coastal = false;
	std::pair<int,int> navalBasePos;
	float navalBaseRot;
	int red,green,blue;
	int id,eu4id;
	stateInterface* state;
	provinceInterface(int iid){id = iid;}
};/*
struct strategicRegionInterface{
	
}*/
struct stateInterface{
	std::vector<provinceInterface*> provinces;
	std::string stateCategory = "wasteland";
	std::vector<std::string> cores;
	std::vector<std::pair<std::string,int>> buildings;
	std::vector<std::tuple<provinceInterface*,std::string,int>> provinceBuildings;
	std::vector<std::pair<std::string,int>> resources;
	std::vector<std::pair<int,int>> victoryPoints;
	std::pair<int,int> center;
	provinceInterface* centerProvince;
	std::string owner = "GER";
	bool capital = false;
	int manpower = 10;
	int pixelCount = 0;
	//bool sea = false;
	int id = -1;
	stateInterface(int iid) : id(iid) {}
	void randomAllStats(){
		std::vector<std::string> categs = {"city","rural","large_city","large_town","metropolis","megalopolis"};
		auto getRandomElement = [](const std::vector<std::string>& vec) -> std::string {
        return vec[std::rand() % vec.size()];
		};
		if(pixelCount>150){stateCategory = getRandomElement(categs);
		manpower = randomNum(500000,5000000);}
		else {stateCategory = "rural";
		manpower = randomNum(50000,500000);}
		
		//print(std::to_string(id)+" "+std::to_string(manpower));
		buildings.push_back(std::make_pair("infrastructure",randomNum(0,4)));
		if(randomNum(0,1))buildings.push_back(std::make_pair("arms_factory",randomNum(1,2)));
		if(randomNum(0,1))buildings.push_back(std::make_pair("industrial_complex",randomNum(1,2)));
		if(randomNum(0,2)==0)buildings.push_back(std::make_pair("air_base",randomNum(3,6)));
		
		if(randomNum(0,4)==0){
			std::vector<std::string> choises = {"oil","aluminium","aluminium","rubber","tungsten","steel","chromium","steel","steel","steel"};
			int res = randomNum(0,2);
			if(res == 0)resources.push_back(std::make_pair(choises[randomNum(0,choises.size()-1)],randomNum(5,15)));
			else if(res == 1)resources.push_back(std::make_pair(choises[randomNum(0,choises.size()-1)],randomNum(25,60)));
			else if(res == 2)resources.push_back(std::make_pair(choises[randomNum(0,choises.size()-1)],randomNum(75,175)));
		}
	}
	void generateFile(){//if(id == -1)return;
		std::string stateString;
		stateString+="state = {\n";//print(1);
		stateString+="\tid = "+std::to_string(id)+"\n";//print(2);
		stateString+="\tname = \"STATE_"+std::to_string(id)+"\"\n";
		stateString+="\tmanpower = "+std::to_string(manpower)+"\n";
		stateString+="\tresources = {\n";
		for(auto i : resources){
			stateString+="\t\t"+i.first+" = "+std::to_string(i.second)+"\n";
		}stateString+="\t}\n";
		stateString+="\tstate_category = "+stateCategory+"\n";
		stateString+="\thistory = {\n";
		stateString+="\t\towner = "+owner+"\n";
		stateString+="\t\tadd_core_of = "+owner+"\n";
		for(auto i : victoryPoints){
			stateString+="\t\tvictory_points = {\n";
			stateString+="\t\t\t"+std::to_string(i.first)+" "+std::to_string(capital?20:i.second)+"\n";
			stateString+="\t\t}\n";
		}
		stateString+="\t\tbuildings = {\n";
		for(auto i : buildings){
			stateString+="\t\t\t"+i.first+" = "+std::to_string(i.second)+"\n";
		}
		//print(5);
		for (const auto& i : provinceBuildings) {
			//print(std::get<1>(i));
			stateString += "\t\t\t" + std::to_string(std::get<0>(i)->id) + " = {" + std::get<1>(i) + " = " + std::to_string(std::get<2>(i)) + "}\n";
		}
		stateString+="\t\t}\n";
		for(auto i : cores){
			stateString+="\t\tadd_core_of = "+i+"\n";
		}
		stateString+="\t}\n";
		stateString+="\tprovinces = {\n\t\t";
		for(auto i : provinces){
			stateString+=std::to_string(i->id)+" ";
		}stateString+="\n\t}\n";
		stateString+="\tlocal_supplies=0.0\n";
		stateString+="}";
		newFile("src/history/states/"+std::to_string(id)+".txt",stateString);
		//return stateString;
	}
};
struct eventControllerClass{
    std::ofstream file;
    std::string contents = "add_namespace = news\n";
    std::vector<eventInterface*> events;
    int newsIdCounter = 100000;
	bool unused = true;
    eventInterface* addEvent(){
		if(unused){init();unused = false;}
        eventInterface* newEvent = new eventInterface();
        newEvent->id = "news."+std::to_string(newsIdCounter++);
        events.push_back(newEvent);
        return newEvent;
    }
    void init(){
        file = newFile("src/events/NewsEventsModded.txt");
    }
    ~eventControllerClass(){
		if(unused){file.close();return;}
        //file<<contents;
        file<<"add_namespace = news\n";
        for(auto ii: events){
			auto i = (*ii);
            file<<"\nnews_event = {";
            file<<"\nid = "<<i.id;
            file<<"\ntitle = "<<localisationController.addLocalization(i.title,"news");
            file<<"\ndesc = "<<localisationController.addLocalization(i.desc,"news");
            file<<"\npicture = "<<i.picture;
            file<<"\nmajor = "<<i.major;
            file<<"\nimmediate = {set_global_flag = "<<i.id<<"}";
            file<<"\ntrigger = {date > 1936.01.2 "<<"NOT = {has_global_flag = "<<i.id<<"}"<<"}";
            file<<"\nmean_time_to_happen = {days = 2}";
            file<<"\nmajor = "<<i.major;
            file<<"\n}";
        }
        file.close();
    }
};
struct countryControllerClass{
	std::vector<countryInterface*> countries;
	std::set<std::string> usedNames;
	bool unused = true;
	countryInterface* addCountry(){
		if(unused){init();unused = false;}
		countryInterface* newCountry = new countryInterface();
		std::string c = "QWERTYUIOPLKJHGFDSAZXCVBNM7896541230";
		newCountry->tag += 'A'+rand()%(('z'+1)-'a');
		newCountry->tag += c[rand()%c.length()];
		newCountry->tag += c[rand()%c.length()];
		countries.push_back(newCountry);
		return newCountry;
	}
	void bookmark(std::vector<countryInterface*> bookmarkCountries){
		std::ofstream bookmarksFile = newFile("src/common/bookmarks/the_gathering_storm.txt");
		bookmarksFile<<"bookmarks = {";
		bookmarksFile<<"\nbookmark = {";
		bookmarksFile<<"\nname = \"GATHERING_STORM_NAME\"";
		bookmarksFile<<"\ndesc = \"GATHERING_STORM_DESC\"";
		bookmarksFile<<"\ndate = 1936.1.1.12";
		bookmarksFile<<"\npicture = \"GFX_select_date_1936\"";
		bookmarksFile<<"\ndefault_country = \""+bookmarkCountries[0]->tag+"\"";
		bookmarksFile<<"\ndefault = yes";
		for(auto i : bookmarkCountries){
			bookmarksFile<<"\n\""+i->tag+"\"={}";
		}
		bookmarksFile<<"\neffect = { randomize_weather = 22345}";
		bookmarksFile<<"\n}}";
		bookmarksFile.close();
	}
	countryInterface* findBiggestCountry(){
		int max = 0;
		countryInterface* maxi;
		for(auto i : countries)if(i->sizeInPixels>max){max = i->sizeInPixels;maxi = i;}
		return maxi;
	}
	std::string generateName(){
		std::vector<std::string> endings = {"ia","tha","ny","land"};
		std::vector<std::string> middle = {"ma","an","ol","ga"};
		std::vector<std::string> start = {"Ro","Por","Den","Ire","Sov"};
		auto getRandomElement = [](const std::vector<std::string>& vec) -> std::string {return vec[std::rand() % vec.size()];};
		std::string name = getRandomElement(start) + getRandomElement(middle) + getRandomElement(endings);
		if(usedNames.find(name) != usedNames.end())name = getRandomElement(start) + getRandomElement(middle) + getRandomElement(endings);
		if(usedNames.find(name) != usedNames.end())name = "New "+name;
		usedNames.insert(name);
		return name;
	}
	void setName(countryInterface* country,std::string name = "nO NamE Had"){
		if(name == "nO NamE Had")name = generateName();
		localisationController.addLocalization(name,country->tag,false);
	}
	void init(){
		std::filesystem::create_directories("src/history/countries");
		std::filesystem::create_directories("src/history/units");
		std::filesystem::create_directories("src/common/country_tags");
		std::filesystem::create_directories("src/common/countries");
		//newFile("");
	}
	~countryControllerClass(){
		if(unused)return;
		std::ofstream tags = std::ofstream("src/common/country_tags/medieval_tags.txt");
		std::ofstream colors = std::ofstream("src/common/countries/colors.txt");
		for (auto i : countries){
			//auto i = (*ii);
			std::ofstream common = std::ofstream("src/common/countries/"+i->tag+".txt");
			std::ofstream history = std::ofstream("src/history/countries/"+i->tag+".txt");
			std::ofstream units = std::ofstream("src/history/units/"+i->tag+".txt");
			tags<<i->tag<<" = \"countries/"<<i->tag<<".txt\"\n";
			common<<"graphical_culture = western_european_gfx";
			common<<"\ngraphical_culture_2d = western_european_2d";
			common<<"\ncolor = { "<<i->red<<" "<<i->green<<" "<<i->blue<<" }";
			history<<"capital = "<<i->capital;
			history<<"\nset_technology = {";
			history<<"infantry_weapons = 1";
			history<<"\nbasic_train = 1";
			history<<"}";
			history<<"\noob = \""<<i->tag<<"\"";
			//history<<"\nset_research_slots = 1";
			history<<"\nset_popularities = { fascism = 100 }";
			history<<"\nset_politics = { ruling_party = fascism";
			history<<"\nlast_election = \"1000.1.1\"";
			history<<"\nelection_frequency = 48";
			history<<"\nelections_allowed = no}";
			//history<<"\nrecruit_character = SOV_nikolay_ustryalov";
			colors<<i->tag<<" = { color = rgb { "<<i->red<<" "<<i->green<<" "<<i->blue<<" }\n";
			colors<<"color_ui = rgb { "<<i->red<<" "<<i->green<<" "<<i->blue<<" }}\n";
			units<<"division_template = {";
			units<<"\nname = \"Local Division\"";
			units<<"\nregiments = {";
			units<<"\ninfantry = { x = 0 y = 0 }";
			units<<"\ninfantry = { x = 0 y = 1 }";
			units<<"\ninfantry = { x = 0 y = 2 }";
			units<<"\ninfantry = { x = 1 y = 0 }";
			units<<"\ninfantry = { x = 1 y = 1 }";
			units<<"\ninfantry = { x = 1 y = 2 }";
			units<<"\ninfantry = { x = 2 y = 0 }";
			units<<"\ninfantry = { x = 2 y = 1 }";
			units<<"\ninfantry = { x = 2 y = 2 }";
			units<<"}";
			units<<"}";
			history.close();
			common.close();
			units.close();
			delete i;
		}
		tags.close();
		colors.close();
	}
};
countryControllerClass countryController;
struct mapClass{
	std::vector<provinceInterface*> provById = std::vector<provinceInterface*>(20000);
	std::vector<stateInterface*> states;
	std::vector<int> provByEu4Id = std::vector<int>(20000);
	std::map<std::tuple<uint8_t,uint8_t,uint8_t>,provinceInterface*> provByColor;
	
	int idCounter = 0;//provinces
	int stateIdCounter = 0;//states
	int strategicRegionIdCounter = 0;//strategicRegion
	BMPImage provinces;
	int mapSize[2] = {5632, 2048};//also max size
	bool unused = true;
	std::set<std::string> usedNames;
	provinceInterface* addProvince(std::tuple<uint8_t,uint8_t,uint8_t> color,int fakeid = 0){
		provinceInterface* province = new provinceInterface(++idCounter);
		provByColor[color] = province;
		province->red = std::get<0>(color);
		province->green = std::get<1>(color);
		province->blue = std::get<2>(color);
		province->eu4id = fakeid;
		//print(int(provById.size()));
		if (provById.size()-1000 < idCounter) {
			int oldSize = provById.size();
			provById.resize(oldSize+20000);provByEu4Id.resize(oldSize+20000);
		}
		provById[idCounter] = province;
		provByEu4Id[fakeid] = idCounter;
		return province;
	}
	stateInterface* addState(int fakeid = 0){
		stateInterface* state = new stateInterface(++stateIdCounter);
		states.push_back(state);
		return state;
	}
	std::string generateName(){
		std::vector<std::string> endings = {"ville","as","ston","son","burg","mer","ers","field"};
		std::vector<std::string> middle = {"th","ing","che","ne","me","sta","en","de","be"};
		std::vector<std::string> start = {"Spring","Alex","Bla","Nash","Jack","Maid","Ox","Bos"};
		auto getRandomElement = [](const std::vector<std::string>& vec) -> std::string {
        return vec[std::rand() % vec.size()];
		};
		std::string name = getRandomElement(start) + getRandomElement(middle) + getRandomElement(endings);
		if(usedNames.find(name) != usedNames.end())name = getRandomElement(start) + getRandomElement(middle) + getRandomElement(endings);
		if(usedNames.find(name) != usedNames.end())name = "New "+name;
		usedNames.insert(name);
		return name;
	}
	void setName(stateInterface* state,std::string name = "nO NamE Had"){
		if(name == "nO NamE Had")name = generateName();
		localisationController.addLocalization(name,"STATE_"+std::to_string(state->id),false);
	}
	void setSize(int w,int h){
		provinces.setSize(w,h);
	}
	void init(){states.push_back(nullptr);
		std::filesystem::create_directories("src/history/states");
		std::filesystem::create_directories("src/map/strategicregions");
		mod.addTag("Map");
		mod.replace.push_back("history/states");
		mod.replace.push_back("history/units");
		mod.replace.push_back("map/strategicregions");
		//mod.replace.push_back("history/countries");//when more than vanilla number of states
	}
	void makeDefinitions(){
		std::ofstream definition = std::ofstream("src/map/definition.csv");
		std::ofstream buildings = std::ofstream("src/map/buildings.txt");
		definition<<"0;0;0;0;land;true;unknown;0";
		std::set<int> usedStates;
		for(int i = 1;i<=idCounter;i++){
			std::string land = "land";
			if(provById[i]->terrain == "ocean")land = "sea";
			if(provById[i]->coastal){
				float x,y;
				x = provById[i]->navalBasePos.first;
				y = provById[i]->navalBasePos.second;
				y -= ((provById[i]->navalBaseRot!=0)?0.5:0);
				buildings<<provById[i]->state->id<<";naval_base;"<<x<<";9.60;"<<y
				<<";"<<provById[i]->navalBaseRot<<";"<<i<<"\n";
				if(usedStates.find(provById[i]->state->id) == usedStates.end())
				buildings<<provById[i]->state->id<<";floating_harbor;"<<provById[i]->center.first<<";9.50;"<<provById[i]->center.second
				<<";0;0\n";
				usedStates.insert(provById[i]->state->id);
			}
			definition<<"\n"<<i<<";"<<provById[i]->red<<";"<<provById[i]->green<<";"<<provById[i]->blue<<";"
			<<land<<";"<<(provById[i]->coastal?"true":"false")<<";"<<provById[i]->terrain<<";1";
		}definition.close();buildings.close();
	}
	void putAllProvincesInSingleRegion(){
		std::ofstream bro = std::ofstream("src/map/strategicregions/mega_region.txt");
		bro<<"strategic_region={\n";
		bro<<"\tid=1\n";
		bro<<"\tname=\"0_region\"\n";
		bro<<"\tprovinces={\n\t";
		for(int i = 1;i<=idCounter;i++){
			bro<<i<<"\n\t\t";
		}
		bro<<"}\n}";
		bro.close();
	}
	void makeStrategicRegion(std::vector<int> provinces){
		strategicRegionIdCounter++;
		std::ofstream bro = std::ofstream("src/map/strategicregions/"+std::to_string(strategicRegionIdCounter)+".txt");
		bro<<"strategic_region={\n";
		bro<<"\tid="+std::to_string(strategicRegionIdCounter)+"\n";
		bro<<"\tname=\""+std::to_string(strategicRegionIdCounter)+"_region\"\n";
		bro<<"\tprovinces={\n\t";
		for(auto i : provinces){
			//print(i);
			bro<<i<<"\n\t\t";
		}
		bro<<"}\n}";
		bro.close();
	}
	/*
	provinceInterface* getCenterProvince(stateInterface* state){
		if(state->centerProvince == 0)return state->provinces[0];
		if(state->centerProvince)return state->provinces[0];
		return state->centerProvince;
	}*/
	void fixAirportsAndrocketsitesAndsupplyhubs(){
		std::ofstream bro = std::ofstream("src/map/airports.txt");
		std::ofstream aag = std::ofstream("src/map/rocketsites.txt");
		std::ofstream supplyHubs = std::ofstream("src/map/supply_nodes.txt");
		//newFile("src/map/supply_nodes.txt","");
		for(int i = 1;i<=stateIdCounter;i++){
			//auto centerProvince = getCenterProvince(states[i]);
			bro<<i<<"={"<<states[i]->centerProvince->id<<"}\n";
			aag<<i<<"={"<<states[i]->provinces[0]->id<<"}\n";
			//if(states[i]->capital||randomNum(1,3) == 3)
				supplyHubs<<"1 "<<states[i]->centerProvince->id<<"\n";
		}
		bro.close();aag.close();supplyHubs.close();
	}
	void emptyFiles(){
		newFile("src/map/weatherpositions.txt","1;500.24;9.90;200.49;small");
		newFile("src/map/positions.txt","");
		newFile("src/map/railways.txt","");
		//newFile("src/map/buildings.txt","");
		newFile("src/map/ambient_object.txt","");
		//newFile("src/map/supply_nodes.txt","");
		newFile("src/map/adjacencies.csv","From;To;Type;Through;start_x;start_y;stop_x;stop_y;adjacency_rule_name;Comment\n-1;-1;;-1;-1;-1;-1;-1;-1");
		newFile("src/map/adjacency_rules.txt","");
		newFile("src/common/ai_strategy/ITA.txt","");
		newFile("src/common/ai_strategy/SOV.txt","");
		newFile("src/common/ai_strategy/GER.txt","");
		newFile("src/common/ai_strategy/ETH.txt","");
		newFile("src/common/ai_strategy/ENG.txt","");
		newFile("src/tutorial/tutorial.txt","tutorial = { }");
		newFile("src/map/cities.txt","types_source = \"map/cities.bmp\"\npixel_step_x = 2\npixel_step_y = 2");
		
		
	}
	void makeUnitStacks(std::string how = "empty"){
		if(how == "empty"){newFile("src/map/unitstacks.txt","");return;}
		std::ifstream file = std::ifstream("my-data/unitstacks.txt");
		std::string line;
		std::vector<std::string> store(idCounter+1);
		for(int i = 1;i<=idCounter;i++){
			std::getline(file, line);
			auto splitted = split(line,";");
			store[i] = ";"+splitted[2]+";"+splitted[3]+";"+splitted[4]+";"+splitted[5]+";"+splitted[6]+"\n";
		}file.close();
		std::ofstream ofile = std::ofstream("src/map/unitstacks.txt");
		for(int ii = 0;ii<=38;ii++){
			for(int i = 1;i<=idCounter;i++){
				ofile<<i<<";"<<ii<<store[i];
			}
			if(ii == 10)ii=20;
			if(ii == 29)ii=37;
		}ofile.close();
		
		
	}
	void fixIfTooFewStates(){
		std::string path = "hoi4-data/history/countries";
		for (const auto & entry : std::filesystem::directory_iterator(path)){
			newFile("src/history/countries/"+between(entry.path().string(),"\\",".txt")+".txt","capital = 1");
		}
			
	}
	void blankTerrainDDS(){
		std::filesystem::copy("hoi4-data/terrain", "src/map/terrain");
	}
	void generateStateFiles(){
		for(int i = 1;i<=stateIdCounter;i++){
			//print(0);
			states[i]->generateFile();
			//print(1);
		}
	}
	void randomMap(){//might not work anymore
		std::srand(static_cast<unsigned int>(GetTickCount()));
		mapSize[0]=512;
		mapSize[1]=512;
		unused = false;init();
		BMPImage image;
		createBMP(mapSize[0],mapSize[1],image,false,"src/map/provinces.bmp");
		generateRandomProvincesOntoBMP(image, 130, 80);//when increasing b, decrease c for performance       130 80
		BMPImage riverimage;
		createBMP(mapSize[0],mapSize[1],riverimage,true,"src/map/rivers.bmp",std::make_tuple(254,254,254),"rivers");
		BMPImage normalimage;
		createBMP(mapSize[0]/2,mapSize[1]/2,normalimage,true,"src/map/world_normal.bmp",std::make_tuple(128,128,255));//b r g
		BMPImage heightimage;
		createBMP(mapSize[0],mapSize[1],heightimage,true,"src/map/heightmap.bmp",std::make_tuple(98,98,98),"heightmap");//y   sea is 89
		BMPImage citiesimage;
		createBMP(mapSize[0],mapSize[1],heightimage,true,"src/map/cities.bmp",std::make_tuple(15,0,0),"cities");//y
		BMPImage treeimage;
		createBMP(mapSize[0],mapSize[1],treeimage,true,"src/map/trees.bmp",std::make_tuple(0,0,0),"trees");//y
		BMPImage terrainimage;
		createBMP(mapSize[0],mapSize[1],terrainimage,true,"src/map/terrain.bmp",std::make_tuple(0,0,0),"terrain");//y
		makeDefinitions();
		putAllProvincesInSingleRegion();
		fixAirportsAndrocketsitesAndsupplyhubs();
		emptyFiles();
		makeUnitStacks();
		fixIfTooFewStates();
		blankTerrainDDS();
	}
	void drawnMap(){
		std::srand(static_cast<unsigned int>(GetTickCount()));
		//mapSize[0]=1024;
		//mapSize[1]=512;
		unused = false;init();
		BMPImage provinces;
		//createBMP(mapSize[0],mapSize[1],image,false,"src/map/provinces.bmp");
		readbmpNoMap("input.bmp", provinces);
		mapSize[0]=provinces.infoHeader.width;
		mapSize[1]=provinces.infoHeader.height;
		deleteBlackBorder(provinces);
		std::ifstream config("config.ini");
		std::string t;
		float optimizationFactor;
		int stateSize,stateSizeOpti;
		int provinceSize,provinceSizeOpti;
		config>>t;config>>stateSize;config>>t;config>>provinceSize;config>>t;config>>optimizationFactor;config.close();
		stateSizeOpti = stateSize*optimizationFactor;
		provinceSizeOpti = provinceSize*optimizationFactor;
		countriesMapIntoStates(provinces,stateSize,stateSizeOpti,provinceSize,provinceSizeOpti);//25 60    50 140  60,160  75,240
		print("provincesed");
		findCoastals(provinces);
		print("land and sea seperated");
		//makeStrategicRegions(provinces);
		finishImage(provinces,"src/map/provinces.bmp");
		BMPImage riverimage;
		createBMP(mapSize[0],mapSize[1],riverimage,true,"src/map/rivers.bmp",std::make_tuple(254,254,254),"rivers");
		BMPImage normalimage;
		createBMP(mapSize[0]/2,mapSize[1]/2,normalimage,true,"src/map/world_normal.bmp",std::make_tuple(128,128,255));//b r g
		BMPImage heightimage,terrainimage;
		createBMP(mapSize[0],mapSize[1],heightimage,false,"src/map/heightmap.bmp",std::make_tuple(98,98,98),"heightmap");//y   sea is 89
		createBMP(mapSize[0],mapSize[1],terrainimage,false,"src/map/terrain.bmp",std::make_tuple(0,0,0),"terrain");//0 15-sea
		landNSeaHeightSeperation(provinces,heightimage,terrainimage);
		//finishImage(heightimage,"src/map/heightmap.bmp",false);
		BMPImage citiesimage;
		createBMP(mapSize[0],mapSize[1],citiesimage,true,"src/map/cities.bmp",std::make_tuple(15,0,0),"cities");//y
		BMPImage treeimage;
		createBMP(mapSize[0],mapSize[1],treeimage,true,"src/map/trees.bmp",std::make_tuple(0,0,0),"trees");//y
		makeDefinitions();
		putAllProvincesInSingleRegion();
		fixAirportsAndrocketsitesAndsupplyhubs();
		emptyFiles();
		makeUnitStacks();
		fixIfTooFewStates();
		blankTerrainDDS();
		generateStateFiles();
		newFile("src/localisation/english/state_names_l_english.yml","");
		newFile("src/localisation/english/countries_l_english.yml","");
		countryInterface* biggestCountry = countryController.findBiggestCountry();
		countryController.bookmark(std::vector<countryInterface*>(1,biggestCountry));
		//generateFlags();
		//biggestCountry->customFocusTree();
		//focusInterface* test = biggestCountry->newFocus();
		//biggestCountry->addFocus(test);
		
		
		//print("job complete");
	}
	~mapClass(){
		
	}
};
mapClass mapController;
eventControllerClass eventController;
struct eu4controllerClass{
	void readDefinitionFile(){
		std::map<std::tuple<uint8_t,uint8_t,uint8_t>,int> usedpixels;
		BMPImage eu4provinces;
		readbmp("eu4-data/map/provinces.bmp",eu4provinces,usedpixels);
		std::string line;
		std::ifstream definition = std::ifstream("eu4-data/map/definition.csv");
		std::getline(definition, line);
		while (std::getline(definition, line)) {
			std::vector<std::string> splt = split(line,";");
			uint8_t red = std::stoi(splt[1]);uint8_t green = std::stoi(splt[2]);uint8_t blue = std::stoi(splt[3]);
			std::tuple<uint8_t,uint8_t,uint8_t> pixelcombo = std::make_tuple(red,green,blue);
			if(usedpixels.find(pixelcombo) == usedpixels.end())continue;
			provinceInterface* province = mapController.addProvince(std::make_tuple(red,green,blue),std::stoi(splt[0]));
			/*province->red = red;
			province->green = green;
			province->blue = blue;*/
		}
		definition.close();
	}
	void readCountriesFile(){
		std::ifstream eu4CountryTags = std::ifstream("eu4-data/country_tags/00_countries.txt");
		std::string line,line2;
		while (std::getline(eu4CountryTags, line)) {
			if(!(isUpper(line[0])&&isUpper(line[1])&&isUpper(line[2])))continue;
			countryInterface* country = countryController.addCountry();
			country->tag = line.substr(0, 3);
			
			std::ifstream eu4CountryFile = std::ifstream("eu4-data/"+between(line,"\""));
			while (std::getline(eu4CountryFile, line2)) {
				if(line2.find("color") == std::string::npos)continue;
				std::stringstream rgb(between(line2,"{","}"));
				rgb>>country->red>>country->green>>country->blue;
				break;
			}
			eu4CountryFile.close();
			
			std::ifstream eu4HistoryCountryFile = 
			std::ifstream("eu4-data/countries/"+country->tag+" - "+between(line,"/","\""));
			while (std::getline(eu4HistoryCountryFile, line2)) {
				if(line2.find("capital") != std::string::npos)
					country->capital = std::stoi(line2.substr(line.find("=")+1));
				if(line2.find("religion") != std::string::npos)country->religion = line2.substr(line.find("=")+1);
				break;
			}
			eu4CountryFile.close();
		}eu4CountryTags.close();
	}
};eu4controllerClass eu4Controller;
//----MAIN----MAIN----MAIN----MAIN----MAIN----MAIN----MAIN----MAIN----MAIN----MAIN
int main(){//system("cls");
/*
	eu4Controller.readCountriesFile();
	eu4Controller.readDefinitionFile();
	print(mapController.idCounter);
	*/
	print("starting");
	//watermark
	mapController.drawnMap();
	//mapController.setSize();
	//system("pause");
}
//eventController.addEvent();
//countryController.addCountry();
void finishImage(BMPImage& image,std::string where,bool headers){
	
	image.openFile(where);
	
	if(headers){
	image.file.write(reinterpret_cast<const char*>(&(image.fileHeader)), sizeof(image.fileHeader));
    image.file.write(reinterpret_cast<const char*>(&(image.infoHeader)), sizeof(image.infoHeader));
	}
	int rowStride = (image.infoHeader.width * 3 + 3) & ~3;
	int32_t height = image.infoHeader.height;
	//print(int(image.pixels.size()));
	
	//std::reverse(image.pixels.begin(), image.pixels.end());
	
	image.file.write(reinterpret_cast<const char*>(image.pixels.data()), rowStride*height);
	image.file.close();
}
void generateRandomProvincesOntoBMP(BMPImage& image, int averageProvinceSize,int chunksize) {
	int numDots = (mapController.mapSize[0]*mapController.mapSize[1])/(averageProvinceSize*averageProvinceSize);
	//numDots = 969;
	//numDots = 3;
	int chunkx = chunksize;
	int chunky = chunksize;
	std::vector<std::vector<std::vector<Dot>>> dots((mapController.mapSize[0]/chunkx)+3, 
	std::vector<std::vector<Dot>>((mapController.mapSize[1]/chunky)+3,std::vector<Dot>()));
	int32_t imageWidth = image.infoHeader.width;
	int32_t imageHeight = image.infoHeader.height;
    const int numCandidates = 2; // Number of candidate points to generate
    const int numIterations = 15; // Number of iterations for candidate selection	
    for (int i = 0; i < numDots; ++i) {
        Dot bestCandidate;
        bestCandidate.x = std::rand() % image.infoHeader.width;
        bestCandidate.y = std::rand() % image.infoHeader.height;
		std::get<0>(bestCandidate.color) = std::rand() % 256;
		std::get<1>(bestCandidate.color) = std::rand() % 256;
		std::get<2>(bestCandidate.color) = std::rand() % 256;
        double bestDistance = 0;
        for (int j = 0; j < numIterations; ++j) {
            int candidateX, candidateY;
            candidateX = std::rand() % image.infoHeader.width;
            candidateY = std::rand() % image.infoHeader.height;
            double minDistance = std::numeric_limits<double>::max();
            for (const auto& dot : dots[candidateX/chunkx][candidateY/chunky]) {
                double distance = std::sqrt((dot.x - candidateX) * (dot.x - candidateX) +
                                            (dot.y - candidateY) * (dot.y - candidateY));
                minDistance = std::min(minDistance, distance);
            }
            if (minDistance > bestDistance) {
                bestCandidate.x = candidateX;
                bestCandidate.y = candidateY;
                bestDistance = minDistance;
            }
        }
		for(int x = -1;x<=1;x++){
		   for(int y = -1;y<=1;y++){
			   int lx = bestCandidate.x/chunkx+x;
			   int ly = bestCandidate.y/chunky+y;
			   if(lx == -1||ly == -1)continue;
			   dots[lx][ly].push_back(bestCandidate);
		   }
	   }
	   
	   provinceInterface* province = mapController.addProvince(bestCandidate.color);/*
	   province->red = std::get<0>(bestCandidate.color);
	   province->green = std::get<1>(bestCandidate.color);
	   province->blue = std::get<2>(bestCandidate.color);*/
	   
	   //print(province->id);
	   
	   stateInterface* state = mapController.addState();
	   state->provinces.push_back(province);
	   state->generateFile();
	   
	   //print(bestCandidate.x,bestCandidate.y);
    }
	
	//print("coloring "+std::to_string(dots.size())+" provinces...");
	print("coloring provinces...");
	//colorization
	int rowStride = (image.infoHeader.width * 3 + 3) & ~3;
	std::vector<uint8_t> row(rowStride);
	std::vector<uint8_t> prevrow;
	std::vector<uint8_t> prevprevrow;
	for (int y = 0; y < image.infoHeader.height; ++y) {
        for (int x = 0; x < image.infoHeader.width; ++x) {
			//int pixelIndex = y * image.infoHeader.width + x;
			/*
			if(!(image.pixels[pixelIndex].red == 255&&
			image.pixels[pixelIndex].green == 0&&
			image.pixels[pixelIndex].blue == 0
			))continue;
			*/
            double minDist = std::numeric_limits<double>::max();
            const Dot* closestDot = nullptr;
            for (const auto& dot : dots[x/chunkx][y/chunky]) {
                double dist = distance(x, y, dot.x, dot.y);
                if (dist < minDist) {
                    minDist = dist;
                    closestDot = &dot;
                }
            }
            //row[x * 3] = std::get<2>(closestDot->color);
            //row[x * 3 + 1] = std::get<1>(closestDot->color);
            //row[x * 3 + 2] = std::get<0>(closestDot->color);
			
			//if(x == image.infoHeader.width-1000)print(y);
			*reinterpret_cast<std::tuple<uint8_t, uint8_t, uint8_t>*>(&row[x * 3]) = closestDot->color;
			
			if(y>0&&x>0){//4 way crossing killer
				std::tuple<uint8_t, uint8_t, uint8_t>& a = *reinterpret_cast<std::tuple<uint8_t, uint8_t, uint8_t>*>(&row[x * 3]);
				std::tuple<uint8_t, uint8_t, uint8_t>& b = *reinterpret_cast<std::tuple<uint8_t, uint8_t, uint8_t>*>(&row[(x-1) * 3]);
				std::tuple<uint8_t, uint8_t, uint8_t>& c = *reinterpret_cast<std::tuple<uint8_t, uint8_t, uint8_t>*>(&prevrow[x * 3]);
				std::tuple<uint8_t, uint8_t, uint8_t>& d = *reinterpret_cast<std::tuple<uint8_t, uint8_t, uint8_t>*>(&prevrow[(x-1) * 3]);
				if (a != b && a != c && a != d && b != c && b != d && c != d) {
					a = b;
				}
			}
			if(y>1&&x>1){//1 pixel killer
				std::tuple<uint8_t, uint8_t, uint8_t>& a = *reinterpret_cast<std::tuple<uint8_t, uint8_t, uint8_t>*>(&row[(x-1) * 3]);
				std::tuple<uint8_t, uint8_t, uint8_t>& b = *reinterpret_cast<std::tuple<uint8_t, uint8_t, uint8_t>*>(&prevrow[(x) * 3]);
				std::tuple<uint8_t, uint8_t, uint8_t>& c = *reinterpret_cast<std::tuple<uint8_t, uint8_t, uint8_t>*>(&prevrow[(x-2) * 3]);
				std::tuple<uint8_t, uint8_t, uint8_t>& d = *reinterpret_cast<std::tuple<uint8_t, uint8_t, uint8_t>*>(&prevprevrow[(x-1) * 3]);
				std::tuple<uint8_t, uint8_t, uint8_t>& e = *reinterpret_cast<std::tuple<uint8_t, uint8_t, uint8_t>*>(&prevrow[(x-1) * 3]);
				if(a != e&&b != e&&c != e&&d != e){
					e = b;
				}
			}
			
        }
		if(prevprevrow.size()>0)image.file.write(reinterpret_cast<const char*>(prevprevrow.data()), rowStride);
		prevprevrow = prevrow;
		prevrow = row;
    }
	image.file.write(reinterpret_cast<const char*>(prevrow.data()), rowStride);
	image.file.write(reinterpret_cast<const char*>(row.data()), rowStride);
	image.file.close();
	print("coloring done");
}
void deleteBlackBorder(BMPImage& image) {
    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(0)));
    
    // Define possible directions: right, left, down, up
    std::vector<std::tuple<int, int>> directions = {
        {0, 1},  // right
        {0, -1}, // left
        {1, 0},  // down
        {-1, 0}  // up
    };
	//int blackPixels = 1;
	//while(blackPixels>0){
	//	blackPixels = 0;
    for (int y = 0; y < image.infoHeader.height; ++y) {
        for (int x = 0; x < image.infoHeader.width; ++x) {
            std::tuple<uint8_t, uint8_t, uint8_t>& a = image.pixels[y * image.infoHeader.width + x];

            if (a != std::make_tuple(0, 0, 0)) continue;
			//blackPixels +=1;
            // Randomize directions
            for (size_t i = 0; i < directions.size(); ++i) {
                size_t j = i + std::rand() / (RAND_MAX / (directions.size() - i) + 1);
                std::swap(directions[i], directions[j]);
            }

            bool changed = false;
            for (const auto& dir : directions) {
                int dy, dx;
                std::tie(dy, dx) = dir;

                int ny = y + dy;
                int nx = x + dx;

                if (ny >= 0 && ny < image.infoHeader.height && nx >= 0 && nx < image.infoHeader.width) {
                    if (image.pixels[ny * image.infoHeader.width + nx] != std::make_tuple(0, 0, 0)) {
                        a = image.pixels[ny * image.infoHeader.width + nx];
                        changed = true;
                        break;
                    }
                }
            }

            // Handle case where no change was made if needed
        }
    }
	//print("black pixels found: "+std::to_string(blackPixels));
	//}
}
struct BoundingBox {
    int minX;
    int minY;
    int maxX;
    int maxY;
	int pixelCount; // New member to store the number of pixels
    BoundingBox() : minX(INT_MAX), minY(INT_MAX), maxX(INT_MIN), maxY(INT_MIN), pixelCount(0) {}
};
void countriesMapIntoStates(BMPImage& image, int averageProvinceSize, int chunksize,int proVaverageProvinceSize,int proVchunksize) {
	std::map<std::tuple<uint8_t, uint8_t, uint8_t>,stateInterface*> states;
    std::map<std::tuple<uint8_t, uint8_t, uint8_t>, BoundingBox> patches;
    for (int y = 0; y < image.infoHeader.height; ++y) {//count bounding box of each country
        for (int x = 0; x < image.infoHeader.width; ++x) {
            auto& pixelColor = image.pixels[y * image.infoHeader.width + x];
            auto& bbox = patches[pixelColor];
            bbox.minX = std::min(bbox.minX, x);
            bbox.minY = std::min(bbox.minY, y);
            bbox.maxX = std::max(bbox.maxX, x);
            bbox.maxY = std::max(bbox.maxY, y);
            bbox.pixelCount++;
        }
    }
	//newFile();
	std::filesystem::create_directories("src/gfx/flags");
	std::filesystem::create_directories("src/gfx/flags/medium");
	std::filesystem::create_directories("src/gfx/flags/small");
    for (auto& entry : patches) {//make states
		const auto& color = entry.first;
        const auto& bbox = entry.second;
	int numDots = (bbox.pixelCount)/(averageProvinceSize*averageProvinceSize);	
	//if(color == std::make_tuple(255,255,255))numDots = (bbox.pixelCount)/((averageProvinceSize*2)*(averageProvinceSize*2));
	if(numDots==0)numDots++;
	if(numDots==1&&bbox.pixelCount>350)numDots++;
	int chunkx = chunksize;
	int chunky = chunksize;
	std::vector<std::vector<std::vector<Dot>>> dots((image.infoHeader.width/chunkx)+3, 
	std::vector<std::vector<Dot>>((image.infoHeader.height/chunky)+3,std::vector<Dot>()));
	int32_t imageWidth = image.infoHeader.width;
	int32_t imageHeight = image.infoHeader.height;
    const int numCandidates = 2; // Number of candidate points to generate
    const int numIterations = 15; // Number of iterations for candidate selection
	countryInterface* country = nullptr;
	if(color != std::make_tuple(255,255,255)){
		
	country = countryController.addCountry();
	//flagger
	{uint16_t widthflag = 82; // Example width
    uint16_t heightflag = 52;
	std::vector<std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>> flagData(widthflag * heightflag);
	for (int y = 0; y < heightflag; ++y) {
		for (int x = 0; x < widthflag; ++x) {
			int scanx,scany;
			int bestRatio = std::max((bbox.maxX-bbox.minX),(bbox.maxY-bbox.minY));
			scanx = (bbox.minX+(bestRatio*(float(x)/widthflag)));
			scany = (bbox.minY+(bestRatio*((float(y)/heightflag))));
			scanx = std::min(image.infoHeader.width-1,scanx);
			scany = std::min(image.infoHeader.height-1,scany);
			auto& pixelColor = image.pixels[scany * image.infoHeader.width + scanx];
			std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>& a = flagData[(y * widthflag + x)];
			//print(bbox.minY,bbox.maxY);
			//print((float(x)/widthflag));
			
			//print(color);
            if(pixelColor == color) a = std::make_tuple(255,200,200,0);
			else a = std::make_tuple(255,std::get<0>(color),std::get<1>(color),std::get<2>(color));
		}
	}writeTGA("src/gfx/flags/"+country->tag+".tga", widthflag, heightflag, flagData);}
		{uint16_t widthflag = 41; // Example width
    uint16_t heightflag = 26;
	std::vector<std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>> flagData(widthflag * heightflag);
	for (int y = 0; y < heightflag; ++y) {
		for (int x = 0; x < widthflag; ++x) {
			int scanx,scany;
			int bestRatio = std::max((bbox.maxX-bbox.minX),(bbox.maxY-bbox.minY));
			scanx = (bbox.minX+(bestRatio*(float(x)/widthflag)));
			scany = (bbox.minY+(bestRatio*((float(y)/heightflag))));
			scanx = std::min(image.infoHeader.width-1,scanx);
			scany = std::min(image.infoHeader.height-1,scany);
			auto& pixelColor = image.pixels[scany * image.infoHeader.width + scanx];
			std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>& a = flagData[(y * widthflag + x)];
			//print(bbox.minY,bbox.maxY);
			//print((float(x)/widthflag));
			
			//print(color);
            if(pixelColor == color) a = std::make_tuple(255,200,200,0);
			else a = std::make_tuple(255,std::get<0>(color),std::get<1>(color),std::get<2>(color));
		}
	}writeTGA("src/gfx/flags/medium/"+country->tag+".tga", widthflag, heightflag, flagData);}
		{uint16_t widthflag = 10; // Example width
    uint16_t heightflag = 7;
	std::vector<std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>> flagData(widthflag * heightflag);
	for (int y = 0; y < heightflag; ++y) {
		for (int x = 0; x < widthflag; ++x) {
			int scanx,scany;
			int bestRatio = std::max((bbox.maxX-bbox.minX),(bbox.maxY-bbox.minY));
			scanx = (bbox.minX+(bestRatio*(float(x)/widthflag)));
			scany = (bbox.minY+(bestRatio*((float(y)/heightflag))));
			scanx = std::min(image.infoHeader.width-1,scanx);
			scany = std::min(image.infoHeader.height-1,scany);
			auto& pixelColor = image.pixels[scany * image.infoHeader.width + scanx];
			std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>& a = flagData[(y * widthflag + x)];
			//print(bbox.minY,bbox.maxY);
			//print((float(x)/widthflag));
			
			//print(color);
            if(pixelColor == color) a = std::make_tuple(255,200,200,0);
			else a = std::make_tuple(255,std::get<0>(color),std::get<1>(color),std::get<2>(color));
		}
	}writeTGA("src/gfx/flags/small/"+country->tag+".tga", widthflag, heightflag, flagData);}
	
	//exit(0);
	//country->frameBox = std::make_pair(std::make_pair(bbox.minX,bbox.minY),std::make_pair(bbox.maxX,bbox.maxY));
	country->sizeInPixels = bbox.pixelCount;
	//print(bbox.pixelCount);
	country->red = std::get<0>(color);
	country->green = std::get<1>(color);
	country->blue = std::get<2>(color);
	country->center = std::make_pair((bbox.minX+bbox.maxX)/2,(bbox.minY+bbox.maxY)/2);
	countryController.setName(country);}
    for (int i = 0; i < numDots; ++i) {
        Dot bestCandidate;
        bestCandidate.x = std::rand() % image.infoHeader.width;
        bestCandidate.y = std::rand() % image.infoHeader.height;
		auto kolor = randomColor();
		while(states.find(kolor)!=states.end()){kolor = randomColor();}
		bestCandidate.color = kolor;
        double bestDistance = 0;
		if(color!=std::make_tuple(255,255,255)){
		states[bestCandidate.color] = mapController.addState();
		states[bestCandidate.color]->owner = country->tag;
		mapController.setName(states[bestCandidate.color]);
		country->states.push_back(states[bestCandidate.color]);
		}
		//states[bestCandidate.color]->sea = true;
        for (int j = 0; j < numIterations; ++j) {
            int candidateX, candidateY;
			candidateX = bbox.minX + std::rand() % (bbox.maxX - bbox.minX + 1);
			candidateY = bbox.minY + std::rand() % (bbox.maxY - bbox.minY + 1);
			auto& a = image.pixels[candidateY * image.infoHeader.width + candidateX];
			//print(j);
			if(a != color){j--;continue;}
			
            double minDistance = std::numeric_limits<double>::max();
            for (const auto& dot : dots[candidateX/chunkx][candidateY/chunky]) {
                double distance = std::sqrt((dot.x - candidateX) * (dot.x - candidateX) +
                                            (dot.y - candidateY) * (dot.y - candidateY));
                minDistance = std::min(minDistance, distance);
            }
            if (minDistance > bestDistance) {
                bestCandidate.x = candidateX;
                bestCandidate.y = candidateY;
                bestDistance = minDistance;
            }
        }
		for(int x = -1;x<=1;x++){
		   for(int y = -1;y<=1;y++){
			   int lx = bestCandidate.x/chunkx+x;
			   int ly = bestCandidate.y/chunky+y;
			   if(lx == -1||ly == -1)continue;
			   dots[lx][ly].push_back(bestCandidate);
		   }
	   }
	   
	  
    }
	int startX = std::max(bbox.minX, 0);
    int startY = std::max(bbox.minY, 0);
    int endX = std::min(bbox.maxX, image.infoHeader.width - 1);
    int endY = std::min(bbox.maxY, image.infoHeader.height - 1);
	
	for (int y = startY; y <= endY; ++y) {
        for (int x = startX; x <= endX; ++x) {
			if(color!=image.pixels[y * image.infoHeader.width + x])continue;
            double minDist = std::numeric_limits<double>::max();
            const Dot* closestDot = nullptr;
            for (const auto& dot : dots[x/chunkx][y/chunky]) {//print();
                double dist = distance(x, y, dot.x, dot.y);
                if (dist < minDist) {
                    minDist = dist;
                    closestDot = &dot;
                }
            }
			image.pixels[y * image.infoHeader.width + x] = closestDot->color;
        }
    }
	//print(endX-startX,endY-startY);
    }
	averageProvinceSize=proVaverageProvinceSize;
	chunksize=proVchunksize;
	patches.clear();
    for (int y = 0; y < image.infoHeader.height; ++y) {//make provinces
        for (int x = 0; x < image.infoHeader.width; ++x) {
            auto& pixelColor = image.pixels[y * image.infoHeader.width + x];
            auto& bbox = patches[pixelColor];
            bbox.minX = std::min(bbox.minX, x);
            bbox.minY = std::min(bbox.minY, y);
            bbox.maxX = std::max(bbox.maxX, x);
            bbox.maxY = std::max(bbox.maxY, y);
            bbox.pixelCount++;
        }
    }
	std::map<std::tuple<uint8_t, uint8_t, uint8_t>,stateInterface*> provinces;
	std::map<std::tuple<uint8_t, uint8_t, uint8_t>,std::pair<int,int>> seaProvinces;
	//std::map<std::tuple<uint8_t, uint8_t, uint8_t>,std::pair<int,int>> provincesBounding;
    for (auto& entry : patches) {
		const auto& color = entry.first;
        const auto& bbox = entry.second;
	int numDots = (bbox.pixelCount)/(averageProvinceSize*averageProvinceSize);
	if(numDots==0)numDots++;
	int chunkx = chunksize;
	int chunky = chunksize;
	std::vector<std::vector<std::vector<Dot>>> dots((image.infoHeader.width/chunkx)+3, 
	std::vector<std::vector<Dot>>((image.infoHeader.height/chunky)+3,std::vector<Dot>()));
	int32_t imageWidth = image.infoHeader.width;
	int32_t imageHeight = image.infoHeader.height;
    const int numCandidates = 2; // Number of candidate points to generate
    const int numIterations = 15; // Number of iterations for candidate selection
	//print(2);
	
	if (states.find(color) == states.end()){// not found
			
			//provinces[color] = nullptr;
			seaProvinces[color] = std::make_pair((bbox.minX+bbox.maxX)/2,(bbox.minY+bbox.maxY)/2);
			provinces[color] = nullptr;
			continue;
		}
	else{
		states[color]->center = std::make_pair((bbox.minX+bbox.maxX)/2,(bbox.minY+bbox.maxY)/2);
		states[color]->pixelCount = bbox.pixelCount;
		//print(std::to_string(states[color]->id)+" "+std::to_string(states[color]->pixelCount));
		//print(states[color]->size);
	}
	
    for (int i = 0; i < numDots; ++i) {
        Dot bestCandidate;
        bestCandidate.x = std::rand() % image.infoHeader.width;
        bestCandidate.y = std::rand() % image.infoHeader.height;
		auto kolor = randomColor();
		//print(int(provinces.size()));
		while(states.find(kolor)!=states.end()||provinces.find(kolor)!=provinces.end()){kolor = randomColor();}
		bestCandidate.color = kolor;
        double bestDistance = 0;
		
		if (states.find(color) != states.end()){
			provinces[bestCandidate.color] = states[color];
			states[color]->center = std::make_pair((bbox.minX+bbox.maxX)/2,(bbox.minY+bbox.maxY)/2);
			//auto &s = patches[a]; 
				//int x = (s.maxX+s.minX)/2;
				//int y = (s.maxY+s.minY)/2;
			//provincesBounding[bestCandidate.color] = std::make_pair(bestCandidate.x,bestCandidate.y);
			/*
		provinceInterface* province = mapController.addProvince(bestCandidate.color);
		states[color]->provinces.push_back(province);
		*/
		}
        for (int j = 0; j < numIterations; ++j) {
            int candidateX, candidateY;
			candidateX = bbox.minX + std::rand() % (bbox.maxX - bbox.minX + 1);
			candidateY = bbox.minY + std::rand() % (bbox.maxY - bbox.minY + 1);
			auto& a = image.pixels[candidateY * image.infoHeader.width + candidateX];
			if(a != color){j--;continue;}
			
            double minDistance = std::numeric_limits<double>::max();
            for (const auto& dot : dots[candidateX/chunkx][candidateY/chunky]) {
                double distance = std::sqrt((dot.x - candidateX) * (dot.x - candidateX) +
                                            (dot.y - candidateY) * (dot.y - candidateY));
                minDistance = std::min(minDistance, distance);
            }
            if (minDistance > bestDistance) {
                bestCandidate.x = candidateX;
                bestCandidate.y = candidateY;
                bestDistance = minDistance;
            }
        }
		
		for(int x = -1;x<=1;x++){
		   for(int y = -1;y<=1;y++){
			   int lx = bestCandidate.x/chunkx+x;
			   int ly = bestCandidate.y/chunky+y;
			   if(lx == -1||ly == -1)continue;
			   dots[lx][ly].push_back(bestCandidate);
		   }
	   }
    }
	int startX = std::max(bbox.minX, 0);
    int startY = std::max(bbox.minY, 0);
    int endX = std::min(bbox.maxX, image.infoHeader.width - 1);
    int endY = std::min(bbox.maxY, image.infoHeader.height - 1);
	//print(3);
	
	for (int y = startY; y <= endY; ++y) {
        for (int x = startX; x <= endX; ++x) {
			//print(1);
			if(color!=image.pixels[y * image.infoHeader.width + x])continue;
            double minDist = std::numeric_limits<double>::max();
            const Dot* closestDot = nullptr;
			//if(dots[x/chunkx][y/chunky].size()==0)print("ERROR! reduce optimization");
            for (const auto& dot : dots[x/chunkx][y/chunky]) {//print();
                double dist = distance(x, y, dot.x, dot.y);
                if (dist < minDist) {
                    minDist = dist;
                    closestDot = &dot;
                }
            }
			//provinces[closestDot->color]++;
			//if()
			image.pixels[y * image.infoHeader.width + x] = closestDot->color;
        }
    }
    }
	
	int crossings = 1;//kill4x crossings
	int singlePixel = 1;
	while(crossings>0||singlePixel>0){
		//std::map<std::tuple<uint8_t, uint8_t, uint8_t>,int> provinces;
		crossings = 0;
		singlePixel = 0;
		for (int y = 0; y < image.infoHeader.height; ++y) {
			if(y>0){
			//scan the world border
				std::tuple<uint8_t, uint8_t, uint8_t>& a = image.pixels[y * image.infoHeader.width + (image.infoHeader.width-1)];
				std::tuple<uint8_t, uint8_t, uint8_t>& b = image.pixels[y * image.infoHeader.width + (0)];
				std::tuple<uint8_t, uint8_t, uint8_t>& c = image.pixels[(y-1) * image.infoHeader.width + (image.infoHeader.width-1)];
				std::tuple<uint8_t, uint8_t, uint8_t>& d = image.pixels[(y-1) * image.infoHeader.width + (0)];
				if (a != b && a != c && a != d && b != c && b != d && c != d) {
					a = c;
					crossings++;
			}}
			for (int x = 0; x < image.infoHeader.width; ++x) {
				if(y>0&&x>0){//4 way crossing killer
				std::tuple<uint8_t, uint8_t, uint8_t>& a = image.pixels[y * image.infoHeader.width + x];
				std::tuple<uint8_t, uint8_t, uint8_t>& b = image.pixels[y * image.infoHeader.width + (x-1)];
				std::tuple<uint8_t, uint8_t, uint8_t>& c = image.pixels[(y-1) * image.infoHeader.width + x];
				std::tuple<uint8_t, uint8_t, uint8_t>& d = image.pixels[(y-1) * image.infoHeader.width + (x-1)];
				if (a != b && a != c && a != d && b != c && b != d && c != d) {
					a = b;
					crossings++;
				}
				}
				if(y>1&&x>1){//1 pixel killer
				std::tuple<uint8_t, uint8_t, uint8_t>& a = image.pixels[y * image.infoHeader.width + (x-1)];
				std::tuple<uint8_t, uint8_t, uint8_t>& b = image.pixels[(y-1) * image.infoHeader.width + (x)];
				std::tuple<uint8_t, uint8_t, uint8_t>& c = image.pixels[(y-1) * image.infoHeader.width + (x-2)];
				std::tuple<uint8_t, uint8_t, uint8_t>& d = image.pixels[(y-2) * image.infoHeader.width + (x-1)];
				std::tuple<uint8_t, uint8_t, uint8_t>& e = image.pixels[(y-1) * image.infoHeader.width + (x-1)];
				if(a != e&&b != e&&c != e&&d != e){
					e = b;
					singlePixel++;
				}
				}
				//provinces[image.pixels[y * image.infoHeader.width + x]]++;
			}
			
		}
		print("4x crossings: "+std::to_string(crossings));
		print("single pixels: "+std::to_string(singlePixel));
		//print("number of real provinces: "+std::to_string(provinces.size()));
	}
	
	for (int y = 0; y < image.infoHeader.height; ++y) {//add final provinces into the game
		for (int x = 0; x < image.infoHeader.width; ++x) {
			std::tuple<uint8_t, uint8_t, uint8_t>& a = image.pixels[y * image.infoHeader.width + x];
			
			if(provinces.find(a)!=provinces.end()){//print(1);
			if(seaProvinces.find(a)!=seaProvinces.end()){
				provinceInterface* province = mapController.addProvince(a);
				//provincesBounding[color] = std::make_pair((bbox.minX+bbox.maxX)/2,(bbox.minY+bbox.maxY)/2);
				province->center = seaProvinces[a];//std::make_pair((bbox.minX+bbox.maxX)/2,(bbox.minY+bbox.maxY)/2);
				province->terrain = "ocean";
				seaProvinces.erase(a);
				provinces.erase(a);
				continue;
			}
				provinceInterface* province = mapController.addProvince(a);
				provinces[a]->provinces.push_back(province);
				province->state = provinces[a];
				//province->center = patches;
				/*
				auto &s = patches[a]; 
				int x = (s.maxX+s.minX)/2;
				int y = (s.maxY+s.minY)/2;*/
				province->center = provinces[a]->center;//;std::make_pair(x,y);
				//print(x,y);
				provinces.erase(a);
			//print(2);
			}
		}
	}
	for(auto i : countryController.countries){
		auto state = i->states[randomNum(0,i->states.size()-1)];
		i->capital = state->id;
		state->capital = true;
		//state->victoryPoints[0].second+=5;
		
	}
	for(auto i : states){
		auto color = image.pixels[(i.second->center.second) * image.infoHeader.width + (i.second->center.first)];
		auto centerProvince = mapController.provByColor[color];
		if(centerProvince->state!=i.second)centerProvince = i.second->provinces[0];
		i.second->victoryPoints.push_back(std::make_pair(centerProvince->id,1));
		i.second->centerProvince = centerProvince;
		i.second->randomAllStats();
		//i.second->generateFile();
	}
	//print("number of real provinces: "+std::to_string(provinces.size()));
	print("number of provinces: "+std::to_string(mapController.idCounter));
	if(mapController.idCounter>65536)print("PROVINCES>65536 GAME WILL CRASH");
	else if(mapController.idCounter>23000)print("PROVINCES>23000 GAME WILL LIKELY CRASH");
	/*for(auto i : mapController.provByColor){
		print(provinces[i.first]);
		//std::cout<<(provinces[i.first])<<"\n";
	}*/
}
void makeStrategicRegions(BMPImage& image){
	int averageProvinceSize = 65;
	int chunksize = 100;
	std::map<std::tuple<uint8_t,uint8_t,uint8_t>,std::vector<int>> strats;
    
    //make states
//const auto& color = entry.first;
        //const auto& bbox = entry.second;
	int numDots = (image.infoHeader.height*image.infoHeader.width)/(averageProvinceSize*averageProvinceSize);
	//if(color == std::make_tuple(255,255,255))numDots = (bbox.pixelCount)/((averageProvinceSize*2)*(averageProvinceSize*2));
	//if(numDots==0)numDots++;
	int chunkx = chunksize;
	int chunky = chunksize;
	std::vector<std::vector<std::vector<Dot>>> dots((image.infoHeader.width/chunkx)+3, 
	std::vector<std::vector<Dot>>((image.infoHeader.height/chunky)+3,std::vector<Dot>()));
	int32_t imageWidth = image.infoHeader.width;
	int32_t imageHeight = image.infoHeader.height;
   const int numCandidates = 2; // Number of candidate points to generate
    const int numIterations = 15; // Number of iterations for candidate selection	
    for (int i = 0; i < numDots; ++i) {
        Dot bestCandidate;
        bestCandidate.x = std::rand() % image.infoHeader.width;
        bestCandidate.y = std::rand() % image.infoHeader.height;/*
		std::get<0>(bestCandidate.color) = std::rand() % 256;
		std::get<1>(bestCandidate.color) = std::rand() % 256;
		std::get<2>(bestCandidate.color) = std::rand() % 256;*/
		bestCandidate.color = randomColor();
        double bestDistance = 0;
        for (int j = 0; j < numIterations; ++j) {
            int candidateX, candidateY;
            candidateX = std::rand() % image.infoHeader.width;
            candidateY = std::rand() % image.infoHeader.height;
            double minDistance = std::numeric_limits<double>::max();
            for (const auto& dot : dots[candidateX/chunkx][candidateY/chunky]) {
                double distance = std::sqrt((dot.x - candidateX) * (dot.x - candidateX) +
                                            (dot.y - candidateY) * (dot.y - candidateY));
                minDistance = std::min(minDistance, distance);
            }
            if (minDistance > bestDistance) {
                bestCandidate.x = candidateX;
                bestCandidate.y = candidateY;
                bestDistance = minDistance;
            }
        }
		for(int x = -1;x<=1;x++){
		   for(int y = -1;y<=1;y++){
			   int lx = bestCandidate.x/chunkx+x;
			   int ly = bestCandidate.y/chunky+y;
			   if(lx == -1||ly == -1)continue;
			   dots[lx][ly].push_back(bestCandidate);
		   }
	   }
	}
	//print(0);
	   //std::map
		std::set<int> used;
		//int cnt = 0;
		for (auto i : mapController.provByColor) {
			auto province = i.second;
			//print(province->id);
			//print(0);
			
			int &x = province->center.first;
			int &y = province->center.second;
			//poses[province->center]++;
			//cnt++;
			//print(1);
			//print(x,y);
			//if(color!=image.pixels[y * image.infoHeader.width + x])continue;
            double minDist = std::numeric_limits<double>::max();
            const Dot* closestDot = nullptr;
			//print(0);
            for (const auto& dot : dots[x/chunkx][y/chunky]) {//print();
                double dist = distance(x, y, dot.x, dot.y);
                if (dist < minDist) {
                    minDist = dist;
                    closestDot = &dot;
                }
            }
			//print(closestDot->color);
			//print(x,y);
			//std::cout<<(closestDot)<<"\n";
			//print(closestDot->color);
			if(strats.find(closestDot->color)==strats.end())strats[closestDot->color] = std::vector<int>();
			//print(2);
			if(used.find(province->id)==used.end())
			strats[closestDot->color].push_back(province->id);
			used.insert(province->id);
			//image.pixels[y * image.infoHeader.width + x] = 
			//print(3);
		}
		/*
	print(int(poses.size()));
	print(cnt);
	for(auto i : poses){
		if(i.second>1)
			print(i.first.first,i.first.second);
		print(i.second);
	}*/
	for(auto i : strats){
		mapController.makeStrategicRegion(i.second);
	}
}
void landNSeaHeightSeperation(BMPImage& provinces,BMPImage& height,BMPImage& terrain){//17
	std::vector<uint8_t> row(height.infoHeader.width);
	std::vector<uint8_t> terrainRow(height.infoHeader.width);
	for (int y = 0; y < provinces.infoHeader.height; ++y) {
		for (int x = 0; x < provinces.infoHeader.width; ++x) {//98,98,98),"heightmap");//y   sea is 89
			if(mapController.provByColor[provinces.pixels[y * provinces.infoHeader.width + x]]->terrain == "ocean")
			{row[x] = 90;
			terrainRow[x] = 15;}
			else {row[x] = 96;terrainRow[x] = 0;}
		}
		height.file.write(reinterpret_cast<const char*>(row.data()),height.infoHeader.width);
		terrain.file.write(reinterpret_cast<const char*>(terrainRow.data()),height.infoHeader.width);
	}
	height.file.close();terrain.file.close();
}
void findCoastals(BMPImage& image){
	for (int y = 0; y < image.infoHeader.height; ++y) {
    for (int x = 0; x < image.infoHeader.width; ++x) {
        // Calculate wrapped indices for the left and right edges
        int botX = (x - 1 + image.infoHeader.width) % image.infoHeader.width;
        int rightX = x;
        int leftX = (x - 2 + image.infoHeader.width) % image.infoHeader.width;

        // For top and bottom edges, clamp the indices
        int rightY = std::max(0, y - 1);
        int topY = std::max(0, y - 2);
        int botY = std::min(image.infoHeader.height - 1, y);
        
        // Adjust indices for border cases
        if (y > 0) {
            rightY = y - 1;
        }
        if (y > 1) {
            topY = y - 2;
        }
        if (y < image.infoHeader.height - 1) {
            botY = y;
        }

        // Access the pixels with appropriate wrapping and clamping
        std::tuple<uint8_t, uint8_t, uint8_t>& bot = image.pixels[botY * image.infoHeader.width + botX];
        std::tuple<uint8_t, uint8_t, uint8_t>& right = image.pixels[rightY * image.infoHeader.width + rightX];
        std::tuple<uint8_t, uint8_t, uint8_t>& left = image.pixels[rightY * image.infoHeader.width + leftX];
        std::tuple<uint8_t, uint8_t, uint8_t>& top = image.pixels[topY * image.infoHeader.width + botX];
        std::tuple<uint8_t, uint8_t, uint8_t>& centr = image.pixels[rightY * image.infoHeader.width + botX];
        
        if (mapController.provByColor[centr]->terrain != "ocean" && mapController.provByColor[centr]->coastal == false && (
            mapController.provByColor[bot]->terrain == "ocean" ||
            mapController.provByColor[top]->terrain == "ocean" ||
            mapController.provByColor[left]->terrain == "ocean" ||
            mapController.provByColor[right]->terrain == "ocean"
        )) {
            mapController.provByColor[centr]->coastal = true;
			 mapController.provByColor[centr]->navalBasePos = std::make_pair(botX,botY);
			 if (mapController.provByColor[top]->terrain == "ocean") {
        mapController.provByColor[centr]->navalBaseRot = 0;  // Facing down
    } else if (mapController.provByColor[bot]->terrain == "ocean") {
        mapController.provByColor[centr]->navalBaseRot = 3.14159;  // Facing up
    } else if (mapController.provByColor[right]->terrain == "ocean") {
        mapController.provByColor[centr]->navalBaseRot =  1.570795 ;  // Facing left
    } else if (mapController.provByColor[left]->terrain == "ocean") {
        mapController.provByColor[centr]->navalBaseRot =  4.712385 ;  // Facing right
    }//print(5);
	//if(mapController.provByColor[centr]->state->provinceBuildings.size()==0)
			//mapController.provByColor[centr]->state->provinceBuildings.push_back(std::make_tuple(mapController.provByColor[centr],"naval_base",randomNum(1,8)));
        }
    }
}


}
