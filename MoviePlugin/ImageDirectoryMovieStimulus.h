//
//  ImageDirectoryMovieStimulus.h
//  MovieStimulusPlugin
//
//  Created by Christopher Stawarz on 8/6/12.
//
//

#ifndef __MovieStimulusPlugin__ImageDirectoryMovieStimulus__
#define __MovieStimulusPlugin__ImageDirectoryMovieStimulus__

#include "BaseMovieStimulus.h"


class ImageDirectoryMovieStimulus : public BaseMovieStimulus {
    
public:
    static const std::string DIRECTORY_PATH;
    
    static void describeComponent(ComponentInfo &info);
    
    explicit ImageDirectoryMovieStimulus(const ParameterValueMap &parameters);
    
    virtual Datum getCurrentAnnounceDrawData();
    
protected:
    virtual int getNumFrames() {
        return images.size();
    }
    
    virtual shared_ptr<Stimulus> getStimulusForFrame(int frameNumber) {
        return images[frameNumber];
    }
    
private:
    const std::string directoryPath;
    std::vector< shared_ptr<Stimulus> > images;
    
};


#endif /* defined(__MovieStimulusPlugin__ImageDirectoryMovieStimulus__) */
