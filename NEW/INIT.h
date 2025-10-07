#include <filesystem>

namespace fs=std::filesystem;
fs::path configDir=fs::current_path();

//是否首次运行检查
bool IsFirstRun();

//  单例模式管理文件路径
class AppConfig
{
    public:
        //删除拷贝赋值操作
        AppConfig(const AppConfig&)=delete;
        AppConfig& operator=(const AppConfig&)=delete;
        //尝试创建实例（确保只返回同一个实例）
        static AppConfig& instance()
        {
            static AppConfig config;
            return config;
        }

        //初始化方法
        void initialize(const fs::path& AppFile);

        //访问方法
        const fs::path WORDS() const{return WORDS_;}
        const fs::path AFTER_WORDS() const{return AFTER_WORDS_;}
        const fs::path PLUSWORDS() const{return PLUSWORDS_;}
        const fs::path PLUSAFTER_WORDS() const{return PLUSAFTER_WORDS_;}
        const fs::path BOOK() const{return BOOK_;}
        const fs::path UPPER_WORDS() const{return UPPER_WORDS_;}

    private:
        AppConfig() : initialized_(false) {};
        void CreatFileIfNotExists(const fs::path&);
        bool initialized_;
        fs::path ConfigFile;
        fs::path WORDS_;
        fs::path AFTER_WORDS_;
        fs::path PLUSWORDS_;
        fs::path PLUSAFTER_WORDS_;
        fs::path BOOK_;
        fs::path UPPER_WORDS_;
};

//正式初始化
int AppConfigInitialize();