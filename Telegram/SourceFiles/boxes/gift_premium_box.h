/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "mtproto/sender.h"

class UserData;

namespace Api {
struct GiftCode;
} // namespace Api

namespace Data {
struct Boost;
struct CreditsHistoryEntry;
struct GiveawayStart;
struct GiveawayResults;
struct SubscriptionEntry;
} // namespace Data

namespace Ui {
class GenericBox;
class VerticalLayout;
} // namespace Ui

namespace Window {
class SessionController;
class SessionNavigation;
} // namespace Window

class GiftPremiumValidator final {
public:
	GiftPremiumValidator(not_null<Window::SessionController*> controller);

	void showBox(not_null<UserData*> user);
	void showChoosePeerBox(const QString &ref);
	void showChosenPeerBox(not_null<UserData*> user, const QString &ref);
	void cancel();

private:
	const not_null<Window::SessionController*> _controller;
	MTP::Sender _api;

	mtpRequestId _requestId = 0;

	rpl::lifetime _manyGiftsLifetime;

};

[[nodiscard]] rpl::producer<QString> GiftDurationValue(int months);
[[nodiscard]] QString GiftDuration(int months);

void GiftCodeBox(
	not_null<Ui::GenericBox*> box,
	not_null<Window::SessionNavigation*> controller,
	const QString &slug);
void GiftCodePendingBox(
	not_null<Ui::GenericBox*> box,
	not_null<Window::SessionNavigation*> controller,
	const Api::GiftCode &data);
void ResolveGiftCode(
	not_null<Window::SessionNavigation*> controller,
	const QString &slug,
	PeerId fromId = 0,
	PeerId toId = 0);

void ResolveGiveawayInfo(
	not_null<Window::SessionNavigation*> controller,
	not_null<PeerData*> peer,
	MsgId messageId,
	std::optional<Data::GiveawayStart> start,
	std::optional<Data::GiveawayResults> results);

void AddCreditsHistoryEntryTable(
	not_null<Window::SessionNavigation*> controller,
	not_null<Ui::VerticalLayout*> container,
	const Data::CreditsHistoryEntry &entry);

void AddSubscriptionEntryTable(
	not_null<Window::SessionNavigation*> controller,
	not_null<Ui::VerticalLayout*> container,
	const Data::SubscriptionEntry &s);
void AddSubscriberEntryTable(
	not_null<Window::SessionNavigation*> controller,
	not_null<Ui::VerticalLayout*> container,
	not_null<PeerData*> peer,
	TimeId date);

void AddCreditsBoostTable(
	not_null<Window::SessionNavigation*> controller,
	not_null<Ui::VerticalLayout*> container,
	const Data::Boost &boost);
