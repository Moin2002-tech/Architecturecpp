//
// Created by moinshaikh on 4/9/26.
//

/*
 * single responsibility architecture
    In short, the single responsibility principle (SRP) means each code unit should have exactly one re-
    sponsibility. This means writing functions that do one thing only, creating types that are responsible
    for a single thing, and creating higher-level components that are focused on one aspect only.
 */

#ifndef ARCHITECTURESINC___FILTERS_HPP
#define ARCHITECTURESINC___FILTERS_HPP

#include "image_loader.hpp"
#include "sketch_filter.hpp"
#include "cartoon_filter.hpp"
#include "image_display.hpp"
enum Filter
{
    sketchs,
    cartoon
};

class Filters
{
private:
    ImageLoader loader;
    SketchFilter sketchFilter;
    CartoonFilter cartoonFilter;
    ImageDisplay display;

public:
    Filters(const std::string& path);
    ~Filters();

    void applyAndShowFilter(enum Filter filter);
    cv::Mat getCurrentImage() const;
};


#endif //ARCHITECTURESINC___FILTERS_HPP
