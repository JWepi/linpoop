
#ifndef DATABUILDER_HH
# define DATABUILDER_HH

class Databuilder
{
  protected:
    std::map<std::string, std::string> strItems;
    std::map<std::string, int> intItems;

  public:
    Databuilder(std::string str);
    Databuilder();
    ~Databuilder();

    void setItem(std::string item, std::string value);
    void setItem(std::string item, int value);
    void setRawItems(std::string str);

    std::string getStrItem(std::string item);
    int getIntItem(std::string item);

    void rmvItem(std::string item);

    void init(std::string str);
    std::string build();
    bool hasItem(std::string item);

    std::map<std::string, std::string> getStrItems();
    std::map<std::string, int> getIntItems();
};

#endif
