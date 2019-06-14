

void APIMachine::Line(const Vec2d&, const Vec2d&, RGBColor);
void APIMachine::RectOutline(const Vec2d&, const Vec2d&, RGBColor);
void APIMachine::RectFilled(const Vec2d&, const Vec2d&, RGBColor);
void APIMachine::Circle(const Vec2d& w, int steps, RGBColor);
void APIMachine::String(const Vec2d w, std::string_view, Font, RGBColor);
Vec2d APIMachine::GetLength(std::string_view);
