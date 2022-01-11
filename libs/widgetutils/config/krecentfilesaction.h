/* This file is part of the KDE libraries
    SPDX-FileCopyrightText: 1999 Reginald Stadlbauer <reggie@kde.org>
    SPDX-FileCopyrightText: 1999 Simon Hausmann <hausmann@kde.org>
    SPDX-FileCopyrightText: 2000 Nicolas Hadacek <haadcek@kde.org>
    SPDX-FileCopyrightText: 2000 Kurt Granroth <granroth@kde.org>
    SPDX-FileCopyrightText: 2000 Michael Koch <koch@kde.org>
    SPDX-FileCopyrightText: 2001 Holger Freyther <freyther@kde.org>
    SPDX-FileCopyrightText: 2002 Ellis Whitehead <ellis@kde.org>
    SPDX-FileCopyrightText: 2003 Andras Mantia <amantia@kde.org>
    SPDX-FileCopyrightText: 2005-2006 Hamish Rodda <rodda@kde.org>
    SPDX-FileCopyrightText: 2022 Alvin Wong <alvin@alvinhc.com>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#ifndef KRECENTFILESACTION_H
#define KRECENTFILESACTION_H

#include <kselectaction.h>
#include <qurl.h>
#include <kritawidgetutils_export.h>

class KConfigGroup;
class KRecentFilesActionPrivate;

class QIcon;

/**
 *  @short Recent files action
 *
 *  This class is an action to handle a recent files submenu.
 *  The best way to create the action is to use KStandardAction::openRecent.
 *  Then you simply need to call loadEntries on startup, saveEntries
 *  on shutdown, addURL when your application loads/saves a file.
 *
 *  @author Michael Koch
 */
class KRITAWIDGETUTILS_EXPORT KRecentFilesAction : public KSelectAction
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KRecentFilesAction)

public:
    /**
     * Constructs an action with the specified parent.
     *
     * @param parent The parent of this action.
     */
    explicit KRecentFilesAction(QObject *parent);

    /**
     * Constructs an action with text; a shortcut may be specified by
     * the ampersand character (e.g. \"&amp;Option\" creates a shortcut with key \e O )
     *
     * This is the most common KAction used when you do not have a
     * corresponding icon (note that it won't appear in the current version
     * of the "Edit ToolBar" dialog, because an action needs an icon to be
     * plugged in a toolbar...).
     *
     * @param text The text that will be displayed.
     * @param parent The parent of this action.
     */
    KRecentFilesAction(const QString &text, QObject *parent);

    /**
     * Constructs an action with text and an icon; a shortcut may be specified by
     * the ampersand character (e.g. \"&amp;Option\" creates a shortcut with key \e O )
     *
     * This is the other common KAction used.  Use it when you
     * \e do have a corresponding icon.
     *
     * @param icon The icon to display.
     * @param text The text that will be displayed.
     * @param parent The parent of this action.
     */
    KRecentFilesAction(const QIcon &icon, const QString &text, QObject *parent);

    /**
     *  Destructor.
     */
    ~KRecentFilesAction() override;

    /**
     * Adds \a action to the list of URLs, with \a url and title \a name.
     *
     * Do not use addAction(QAction*), as no url will be associated, and
     * consequently urlSelected() will not be emitted when \a action is selected.
     */
    void addAction(QAction *action, const QUrl &url, const QString &name);

    /**
     * Reimplemented for internal reasons.
     */
    QAction *removeAction(QAction *action) override;

public Q_SLOTS:
    /**
     * Clears the recent files list.
     * Note that there is also an action shown to the user for clearing the list.
     */
    virtual void clear();

public:
    /**
     *  Loads the recent files entries from a given KConfigGroup object.
     *  You can provide the name of the group used to load the entries.
     *  If the groupname is empty, entries are loaded from a group called 'RecentFiles'.
     *  Local file entries that do not exist anymore are not restored.
     *
     */
    void loadEntries(const KConfigGroup &config);

    /**
     *  Saves the current recent files entries to a given KConfigGroup object.
     *  You can provide the name of the group used to load the entries.
     *  If the groupname is empty, entries are saved to a group called 'RecentFiles'
     *
     */
    void saveEntries(const KConfigGroup &config);

    /**
     *  Add URL to recent files list.
     *
     *  @param url The URL of the file
     *  @param name The user visible pretty name that appears before the URL
     */
    void addUrl(const QUrl &url, const QString &name = QString());

    /**
     *  Remove an URL from the recent files list.
     *
     *  @param url The URL of the file
     */
    void removeUrl(const QUrl &url);

    /**
     *  Retrieve a list of all URLs in the recent files list.
     */
    QList<QUrl> urls() const;

    void setUrlIcon(const QUrl &url, const QIcon &icon);

Q_SIGNALS:
    /**
     *  This signal gets emitted when the user selects a URL.
     *
     *  @param url The URL that the user selected.
     */
    void urlSelected(const QUrl &url);

    /**
     *  This signal gets emitted when the user clear list.
     *  So when user stores url in specific config file it can saveEntry.
     *  @since 4.3
     */
    void recentListCleared();

private:
    //Internal
    void clearEntries();
    // Don't warn about the virtual overload. As the comment of the other
    // addAction() says, addAction( QAction* ) should not be used.
    using KSelectAction::addAction;

    KRecentFilesActionPrivate *d_ptr;

    Q_PRIVATE_SLOT(d_func(), void _k_urlSelected(QAction *))

    void rebuildEntries();

private Q_SLOTS:
    void fileAdded(const QUrl &url);
    void fileRemoved(const QUrl &url);
    void listRenewed();
};

#endif
