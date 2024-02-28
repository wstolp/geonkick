
class PresetMetadata {
public:
        PresetMetadata(const std::string &file = std::string());
        PresetMetadata(const rapidjson::Value &presetObj);
        std::string toJson() const;
        
 private:
        std::string name;
        std::string author;
        std::string liecense;
        std::string url;
        std::string category;
};
