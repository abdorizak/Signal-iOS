//
// Copyright 2021 Signal Messenger, LLC
// SPDX-License-Identifier: AGPL-3.0-only
//

#import <SignalServiceKit/TSOutgoingMessage.h>

@class TSContactThread;

NS_ASSUME_NONNULL_BEGIN

@interface OWSOutgoingSenderKeyDistributionMessage : TSOutgoingMessage

- (instancetype)initOutgoingMessageWithBuilder:(TSOutgoingMessageBuilder *)outgoingMessageBuilder
                        recipientAddressStates:
                            (NSDictionary<SignalServiceAddress *, TSOutgoingMessageRecipientState *> *)
                                recipientAddressStates NS_UNAVAILABLE;
- (instancetype)initOutgoingMessageWithBuilder:(TSOutgoingMessageBuilder *)outgoingMessageBuilder
                          additionalRecipients:(NSArray<ServiceIdObjC *> *)additionalRecipients
                            explicitRecipients:(NSArray<AciObjC *> *)explicitRecipients
                             skippedRecipients:(NSArray<ServiceIdObjC *> *)skippedRecipients
                                   transaction:(DBReadTransaction *)transaction NS_UNAVAILABLE;

- (instancetype)initWithThread:(TSContactThread *)destinationThread
    senderKeyDistributionMessageBytes:(NSData *)skdmBytes
                          transaction:(DBReadTransaction *)transaction;

/// Returns YES if this message is being sent as a precondition to sending an online-only message.
/// Typing indicators are only delivered to online devices. Since they're ephemeral we just don't bother sending a
/// typing indicator to a recipient if we need the user to verify a safety number change. Outgoing SKDMs being sent on
/// behalf of an outgoing typing indicator should inherit this behavior.
@property (assign, atomic, readonly) BOOL isSentOnBehalfOfOnlineMessage;
/// Returns YES if this message is being sent as a precondition to sending a story message.
@property (assign, atomic, readonly) BOOL isSentOnBehalfOfStoryMessage;
- (void)configureAsSentOnBehalfOf:(TSOutgoingMessage *)message
                         inThread:(TSThread *)thread NS_SWIFT_NAME(configureAsSentOnBehalfOf(_:in:));

@end

NS_ASSUME_NONNULL_END
