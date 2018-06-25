/*
*	File:		Golem.h
*	
*	Version:	1.0
* 
*	Created:	10/17/09
*	
*	Copyright:  Copyright � 2009 Airwindows, All Rights Reserved
* 
*	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc. ("Apple") in 
*				consideration of your agreement to the following terms, and your use, installation, modification 
*				or redistribution of this Apple software constitutes acceptance of these terms.  If you do 
*				not agree with these terms, please do not use, install, modify or redistribute this Apple 
*				software.
*
*				In consideration of your agreement to abide by the following terms, and subject to these terms, 
*				Apple grants you a personal, non-exclusive license, under Apple's copyrights in this 
*				original Apple software (the "Apple Software"), to use, reproduce, modify and redistribute the 
*				Apple Software, with or without modifications, in source and/or binary forms; provided that if you 
*				redistribute the Apple Software in its entirety and without modifications, you must retain this 
*				notice and the following text and disclaimers in all such redistributions of the Apple Software. 
*				Neither the name, trademarks, service marks or logos of Apple Computer, Inc. may be used to 
*				endorse or promote products derived from the Apple Software without specific prior written 
*				permission from Apple.  Except as expressly stated in this notice, no other rights or 
*				licenses, express or implied, are granted by Apple herein, including but not limited to any 
*				patent rights that may be infringed by your derivative works or by other works in which the 
*				Apple Software may be incorporated.
*
*				The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO WARRANTIES, EXPRESS OR 
*				IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY 
*				AND FITNESS FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE 
*				OR IN COMBINATION WITH YOUR PRODUCTS.
*
*				IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR CONSEQUENTIAL 
*				DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
*				OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, 
*				REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER 
*				UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN 
*				IF APPLE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
#include "AUEffectBase.h"
#include "GolemVersion.h"

#if AU_DEBUG_DISPATCHER
	#include "AUDebugDispatcher.h"
#endif


#ifndef __Golem_h__
#define __Golem_h__


#pragma mark ____Golem Parameters

static const float kDefaultValue_ParamOne = 0.0;
static const float kDefaultValue_ParamTwo = 0.0;
static CFStringRef kParameterThreeName = CFSTR("Phase");
static const int kIn = 1;
static const int kOut = 2;
static const int kBassIn = 3;
static const int kBassOut = 4;
static const int kTiming = 5;
static const int kBoth = 6;
static const int kDefaultValue_ParamThree = kIn;

//let's assume we always have a default of 0.0, for no effect

static CFStringRef kParameterOneName = CFSTR("Balance");
static CFStringRef kParameterTwoName = CFSTR("Offset");
//Alter the name if desired, but using the plugin name is a start

static CFStringRef kMenuItem_In = CFSTR ("Reinforcement- Two Mics Range");
static CFStringRef kMenuItem_Out = CFSTR ("Cancellation- Two Mics Range");
static CFStringRef kMenuItem_BassIn = CFSTR ("Reinforcement- Amp/DI Range");
static CFStringRef kMenuItem_BassOut = CFSTR ("Cancellation- Amp/DI Range");
static CFStringRef kMenuItem_Timing = CFSTR ("Defeat Timing Adjustment");
static CFStringRef kMenuItem_Both = CFSTR ("Defeat Timing & Gain");


enum {
	kParam_One =0,
	kParam_Two =1,
	kParam_Three =2,
	//Add your parameters here...
	kNumberOfParameters=3
};

#pragma mark ____Golem
class Golem : public AUEffectBase
{
public:
	Golem(AudioUnit component);
#if AU_DEBUG_DISPATCHER
	virtual ~Golem () { delete mDebugDispatcher; }
#endif
	
	virtual ComponentResult Reset(AudioUnitScope inScope, AudioUnitElement inElement);

	virtual OSStatus ProcessBufferLists(AudioUnitRenderActionFlags & ioActionFlags, 
						const AudioBufferList & inBuffer, AudioBufferList & outBuffer, 
						UInt32 inFramesToProcess);

	virtual	ComponentResult		GetParameterValueStrings(AudioUnitScope			inScope,
														 AudioUnitParameterID		inParameterID,
														 CFArrayRef *			outStrings);
    
	virtual	ComponentResult		GetParameterInfo(AudioUnitScope			inScope,
												 AudioUnitParameterID	inParameterID,
												 AudioUnitParameterInfo	&outParameterInfo);
    
	virtual ComponentResult		GetPropertyInfo(AudioUnitPropertyID		inID,
												AudioUnitScope			inScope,
												AudioUnitElement		inElement,
												UInt32 &			outDataSize,
												Boolean	&			outWritable );
	
	virtual ComponentResult		GetProperty(AudioUnitPropertyID inID,
											AudioUnitScope 		inScope,
											AudioUnitElement 		inElement,
											void *			outData);

	virtual UInt32 SupportedNumChannels(const AUChannelInfo ** outInfo);
	
	virtual ComponentResult    Initialize();
 	virtual	bool				SupportsTail () { return true; }
    virtual Float64				GetTailTime() {return 1.0/GetSampleRate()*30.0;}
    virtual Float64				GetLatency() {return 0.0;}
 									
	/*! @method Version */
	virtual ComponentResult	Version() { return kGolemVersion; }
private:    
	Float64 p[4099];
	int count;
	long double fpNShapeAL;
	long double fpNShapeBL;
	long double fpNShapeAR;
	long double fpNShapeBR;
	bool flip;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#endif