//
//          Copyright (c) 2016, Scientific Toolworks, Inc.
//
// This software is licensed under the MIT License. The LICENSE.md file
// describes the conditions under which this software may be distributed.
//
// Author: Jason Haslam
//

#include "Signature.h"
#include "git2/signature.h"
#include <QDateTime>
#include <QTimeZone>

namespace git {

Signature::Signature(git_signature *signature, bool owned)
  : d(signature, owned ? git_signature_free : [](git_signature *) {})
{}

Signature::operator const git_signature *() const
{
  return d.data();
}

QString Signature::name() const
{
  return d->name;
}

QString Signature::email() const
{
  return d->email;
}

QDateTime Signature::date() const
{
  int offset = d->when.offset * 60; // Convert from minutes to seconds.
  return QDateTime::fromSecsSinceEpoch(d->when.time, QTimeZone(offset));
}

QString Signature::initials() const
{
  return initials(name());
}

QString Signature::initials(const QString &name)
{
  QStringList names = name.split(' ');
  QStringList initials(names.first().left(1).toUpper());
  if (names.size() > 1)
    initials.append(names.last().left(1).toUpper());
  return initials.join(QString());
}

} // namespace git
