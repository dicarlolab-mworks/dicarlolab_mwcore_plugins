/*
 *  MovieStimulusFactory.cpp
 *  MovieStimulus
 *
 *  Created by Christopher Stawarz on 3/9/11.
 *  Copyright 2011 MIT. All rights reserved.
 *
 */

#include <MWorksCore/ComponentRegistry.h>

#include "MovieStimulusFactory.h"
#include "MovieStimulus.h"

using namespace mw;


void BaseMovieStimulusFactory::getBaseMovieParameters(std::map<std::string, std::string> &parameters,
                                                      ComponentRegistry *reg,
                                                      std::string &tag,
                                                      shared_ptr<Variable> &framesPerSecond,
                                                      shared_ptr<Variable> &ended,
                                                      shared_ptr<Variable> &loop)
{
    const char *TAG = "tag";
    const char *FRAMES_PER_SECOND = "frames_per_second";
    const char *ENDED = "ended";
    const char *LOOP = "loop";
    
    REQUIRE_ATTRIBUTES(parameters,
                       TAG,
                       FRAMES_PER_SECOND);
    
    tag = parameters[TAG];
    
    framesPerSecond = reg->getVariable(parameters[FRAMES_PER_SECOND]);
    CHECK_ATTRIBUTE(framesPerSecond, parameters, FRAMES_PER_SECOND);
    
    if (!(parameters[ENDED].empty())) {
        ended = reg->getVariable(parameters[ENDED]);
        CHECK_ATTRIBUTE(ended, parameters, ENDED);
    }
    
    loop = reg->getVariable(parameters[LOOP], "0");
    CHECK_ATTRIBUTE(loop, parameters, LOOP);
}


shared_ptr<mw::Component> MovieStimulusFactory::createObject(std::map<std::string, std::string> parameters,
                                                             ComponentRegistry *reg)
{
    const char *STIMULUS_GROUP = "stimulus_group";
    
    REQUIRE_ATTRIBUTES(parameters, STIMULUS_GROUP);
    
    std::string tag;
    shared_ptr<Variable> framesPerSecond;
    shared_ptr<Variable> ended;
    shared_ptr<Variable> loop;
    getBaseMovieParameters(parameters, reg, tag, framesPerSecond, ended, loop);
    
    shared_ptr<StimulusGroup> stimulusGroup(reg->getObject<StimulusGroup>(parameters[STIMULUS_GROUP]));
    CHECK_ATTRIBUTE(stimulusGroup, parameters, STIMULUS_GROUP);
    
    shared_ptr<MovieStimulus> newMovie(new MovieStimulus(tag,
                                                         framesPerSecond,
                                                         stimulusGroup,
                                                         ended,
                                                         loop));
    
    // To preserve existing behavior, *do not* load stimulus here
    shared_ptr<StimulusNode> node(new StimulusNode(newMovie));
    reg->registerStimulusNode(tag, node);
    
    return newMovie;
}


shared_ptr<mw::Component>
ImageDirectoryMovieStimulusFactory::createObject(std::map<std::string, std::string> parameters, ComponentRegistry *reg)
{
    const char *DIRECTORY_PATH = "directory_path";
    const char *X_SIZE = "x_size";
    const char *Y_SIZE = "y_size";
    const char *X_POSITION = "x_position";
    const char *Y_POSITION = "y_position";
    const char *ROTATION = "rotation";
    const char *ALPHA_MULTIPLIER = "alpha_multiplier";
    const char *DEFERRED = "deferred";
    
    REQUIRE_ATTRIBUTES(parameters,
                       DIRECTORY_PATH,
                       X_SIZE,
                       Y_SIZE);
    
    std::string tag;
    shared_ptr<Variable> framesPerSecond;
    shared_ptr<Variable> ended;
    shared_ptr<Variable> loop;
    getBaseMovieParameters(parameters, reg, tag, framesPerSecond, ended, loop);
    
    boost::filesystem::path directoryPath(reg->getPath(parameters["working_path"], parameters[DIRECTORY_PATH]));
    
    shared_ptr<Variable> xSize(reg->getVariable(parameters[X_SIZE]));
    CHECK_ATTRIBUTE(xSize, parameters, X_SIZE);
    
    shared_ptr<Variable> ySize(reg->getVariable(parameters[Y_SIZE]));
    CHECK_ATTRIBUTE(ySize, parameters, Y_SIZE);
    
    shared_ptr<Variable> xPosition(reg->getVariable(parameters[X_POSITION], "0.0"));
    CHECK_ATTRIBUTE(xPosition, parameters, X_POSITION);
    
    shared_ptr<Variable> yPosition(reg->getVariable(parameters[Y_POSITION], "0.0"));
    CHECK_ATTRIBUTE(yPosition, parameters, Y_POSITION);
    
    shared_ptr<Variable> rotation(reg->getVariable(parameters[ROTATION], "0.0"));
    CHECK_ATTRIBUTE(rotation, parameters, ROTATION);
    
    shared_ptr<Variable> alphaMultiplier(reg->getVariable(parameters[ALPHA_MULTIPLIER], "1.0"));
    CHECK_ATTRIBUTE(alphaMultiplier, parameters, ALPHA_MULTIPLIER);
    
    shared_ptr<ImageDirectoryMovieStimulus> newMovie(new ImageDirectoryMovieStimulus(tag,
                                                                                     directoryPath.string(),
                                                                                     xSize,
                                                                                     ySize,
                                                                                     xPosition,
                                                                                     yPosition,
                                                                                     rotation,
                                                                                     alphaMultiplier,
                                                                                     framesPerSecond,
                                                                                     ended,
                                                                                     loop));
    
    newMovie->setDeferredFromString(parameters[DEFERRED]);
    if (newMovie->getDeferred() == Stimulus::nondeferred_load) {
        newMovie->load(StimulusDisplay::getCurrentStimulusDisplay());
    }
    
    shared_ptr<StimulusNode> node(new StimulusNode(newMovie));
    reg->registerStimulusNode(tag, node);
    
    return newMovie;
}






















