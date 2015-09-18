//
//  AppRight.h
//  iWatcher
//
//  Created by gryphonet on 1/21/14.
//  Copyright (c) 2014 Gil Lederman. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 * @defined ADD_MARKER(message)
 * @abstract Abstract for this API.
 * @discussion A shot function that create report a new bug to the Gryphonet AppRight database.
 * @see AppRight#addMarkerWithMessage
 */
#define ADD_MARKER(message)  [AppRight addMarkerWithMessage:message withFileName:@__FILE__ withClassName:[NSString stringWithFormat:@"%s", __PRETTY_FUNCTION__] withMethod:[NSString stringWithFormat:@"%s", __PRETTY_FUNCTION__] withLineNumber:__LINE__];

/*!
 * @typedef ARLifeCyclePhase
 * @abstract Abstract for this API.
 * @discussion The enum constant of this type with the specified name.
 * @constant ARLifeCyclePhaseRelease A 'Release' name.
 * @constant ARLifeCyclePhaseDevelopment A 'Development' name.
 */
typedef NS_ENUM(NSUInteger, ARLifeCyclePhase) {
    /*! Release mode */
    ARLifeCyclePhaseRelease = 0,
    /*! Development mode */
    ARLifeCyclePhaseDevelopment = 1
};

typedef NS_ENUM(NSUInteger, JSAction){
    JSActionSendNow = 0,
    JSActionReprotBug = 1,
    JSActionReportException = 2,
    JSActionAddMarker = 3,
    JSActionReportJsError = 4
};

/*!
 * @class AppRight
 * @brief The AppRight class is used to access the various services of Gryphonet AppRight SDK.
 * @author Gryphonet http://gryphonet.com
 */
@interface AppRight : NSObject
/*!
 * @brief Starts the Gryphonet AppRight service.
 * @param accountID The account id is provided when registering.
 * @param lifecyclePhase The application lifecycle phase "development" or "release".
 * @code
     NSString* accountId = @"<your account id>";
     ARLifeCyclePhase* lifeCyclePhase = ARLifeCyclePhaseRelease;
     #ifdef DEBUG
         lifeCyclePhase = ARLifeCyclePhaseDevelopment;
     #endif
     [AppRight startWithAccountID:accountId withLifeCyclePhase:lifeCyclePhase];
 * @endcode
 */
+ (void) startWithAccountID:(NSString*)accountID withLifeCyclePhase:(ARLifeCyclePhase)lifecyclePhase;
/*!
 * @brief Reports a new Marker to the Gryphonet AppRight database.
 * @see @b macros ADD_MARKER(message)
 * @param message Your mark in the code.
 * @param filename Your filename.
 * @param className Your class name.
 * @param method Your method.
 * @param lineNumber line number.
 * @code
     -(void) myCustomLoopChecker:(int)loops {
         for (int i = 0; i < loops; i++) {
             //do something
             if (loops > LOOP_THRESHOLD) {
                 ADD_MARKER(@"loop was above threshold.");
             break;
             }
         }
     }
 * @endcode
 */
+ (void) addMarkerWithMessage: (NSString*) message withFileName:(NSString*)filename withClassName:(NSString*)className withMethod:(NSString*)method withLineNumber:(int)lineNumber;
/*!
 * @brief Reports a new bug to the Gryphonet AppRight database.
 * @param message A short message describing the bug.
 * @return BOOL
 * @code
     int input = -1;
     if (input < 0) {
         [AppRight reportBugWithMessage:@"runAlgorithm: input is negative"];
     }
 * @endcode
 */
+ (BOOL) reportBugWithMessage:(NSString*)message;
/*!
 * @brief Reports a new exception to the Gryphonet AppRight database.
 * @param exception The exception object being reported.
 * @return BOOL
 * @code
     @try {
         if (input < 0) {
             //ToDo
             NSException *e = [NSException exceptionWithName:@"CheckValue"
                 reason:@"*** The value 'input' < 0"
                 userInfo:nil];
             @throw e;
         }
     } 
     @catch (NSException* ex) {
         [AppRight reportExceptionWithInfo:ex];
     }
 * @endcode
 */
+ (BOOL) reportExceptionWithInfo:(NSException*)exception;
/*!
 * @brief Send all captured events.
 * @return BOOL
 * @code
     [AppRight sendNow];
 * @endcode
 */
+ (BOOL) sendNow;
+ (BOOL) handleFromJS:(JSAction)javascriptAction withEventArgs:(NSArray*)args;

/*!
 * @brief Sets user class
 *
 * @param userclass the new userclass
 */
+ (void) setUserClass:(NSString*) userclass;

/*!
 * @brief Clears all previously set user data from captured events
 */
+ (void) clearUserClass;

/*!
 * @brief Sets start point of zone
 *
 * @param zoneName The zone name
 */
+ (void) startZone:(NSString*) zoneName;

/*!
 * @brief exit zone
 */
+ (void) stopZone;

/*!
 * @brief Sets user metadata for custom key
 *
 * @param key The key of user metadata
 * @param value The user metadata value
 */
+ (void) putUserMetadata:(NSString*)key value:(NSString*)value;

/*!
 * @brief Remove user metadata for custom key
 *
 * @param key The key of user metadata
 */
+ (void) clearUserMetadata:(NSString*)key;

/*!
 * @brief Remove all user metadata
 */
+ (void) clearAllUserMetadata;

@end

