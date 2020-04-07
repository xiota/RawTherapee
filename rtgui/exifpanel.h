/*
 *  This file is part of RawTherapee.
 *
 *  Copyright (c) 2004-2010 Gabor Horvath <hgabor@rawtherapee.com>
 *
 *  RawTherapee is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  RawTherapee is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RawTherapee.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include <memory>

#include <gtkmm.h>

#include "toolpanel.h"

namespace rtengine
{

namespace procparams
{

class ExifPairs;

}

}

class ExifPanel final :
    public Gtk::Box,
    public ToolPanel
{

private:
    const rtengine::FramesMetaData* idata;
    const std::unique_ptr<rtengine::procparams::ExifPairs> changeList;
    const std::unique_ptr<rtengine::procparams::ExifPairs> defChangeList;

    class ExifColumns : public Gtk::TreeModelColumnRecord
    {
    public:
        Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > icon;
        Gtk::TreeModelColumn<Glib::ustring> key;
        Gtk::TreeModelColumn<Glib::ustring> label;
        Gtk::TreeModelColumn<Glib::ustring> value;
        Gtk::TreeModelColumn<Glib::ustring> value_nopango;
        Gtk::TreeModelColumn<bool> editable;
        Gtk::TreeModelColumn<bool> edited;

        ExifColumns()
        {
            add(key);
            add(label);
            add(value);
            add(icon);
            add(edited);
            add(value_nopango);
            add(editable);
        }
    };
    Glib::RefPtr<Gdk::Pixbuf> keepicon;
    Glib::RefPtr<Gdk::Pixbuf> editicon;

    ExifColumns exifColumns;
    Gtk::TreeView* exifTree;
    Gtk::ScrolledWindow* scrolledWindow;
    Glib::RefPtr<Gtk::TreeStore> exifTreeModel;

    Gtk::Button* add;
    Gtk::Button* reset;
    Gtk::Button* resetAll;

    const std::vector<std::pair<std::string, Glib::ustring>> editableTags;

    void addTag(const std::string &key, const Glib::ustring &label, const Glib::ustring &value, bool editable, bool edited);
    void refreshTags();
    void resetIt(const Gtk::TreeModel::const_iterator& iter);
    void resetPressed();
    void resetAllPressed();
    void addPressed();

public:
    ExifPanel ();
    ~ExifPanel() override;

    void read (const rtengine::procparams::ProcParams* pp, const ParamsEdited* pedited = nullptr) override;
    void write (rtengine::procparams::ProcParams* pp, ParamsEdited* pedited = nullptr) override;
    void setDefaults (const rtengine::procparams::ProcParams* defParams, const ParamsEdited* pedited = nullptr) override;

    void setImageData (const rtengine::FramesMetaData* id);

    void exifSelectionChanged();
    // void row_activated (const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);

    void notifyListener();

};
