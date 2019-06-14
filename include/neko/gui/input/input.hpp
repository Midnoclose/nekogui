
namespace neko::gui {

class Key {
public:
    class Special {
    public:
        Special();
        Special(std::initializer_list<char> special); // use c, s, a
        Special(std::initializer_list<std::string_view> special); // use ctrl, shift, alt
        static Special Get()
        bool ctrl = false;
        bool shift = false;
        bool alt = false;
    };
    Key(char k);
    Key(char k, const Special special);
    inline char k GetChar() { return k; }
    inline bool HasCtrl() { return this->ctrl; }
    inline bool HasShift() { return this->shift; }
    inline bool HasAlt() { return this->alt; }
    bool Test();
    static std::unordered_set<Key> GetAll();
private:
    const char k;
}


}
