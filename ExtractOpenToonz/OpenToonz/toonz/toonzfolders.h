#pragma once

#ifndef TOONZFOLDERS_INCLUDED
#define TOONZFOLDERS_INCLUDED

#include "../tfilepath.h"

#undef DVAPI
#undef DVVAR
#ifdef TOONZLIB_EXPORTS
#define DVAPI DV_EXPORT_API
#define DVVAR DV_EXPORT_VAR
#else
#define DVAPI DV_IMPORT_API
#define DVVAR DV_IMPORT_VAR
#endif

#include <set>

namespace ToonzFolder {

TFilePath getModulesDir();
TFilePath getTemplateModuleDir();
TFilePath getMyModuleDir();

TFilePath getRoomsDir();
TFilePath getTemplateRoomsDir();
TFilePath getMyRoomsDir();
TFilePath getRoomsFile(TFilePath filename);
TFilePath getRoomsFile(std::string fn);

// restituisce getMyModuleDir() + filename
// o getTemplateModuleDir() + filename
TFilePath getModuleFile(TFilePath filename);
TFilePath getModuleFile(std::string fn);

TFilePathSet getProjectsFolders();
TFilePath getFirstProjectsFolder();
TFilePath getStudioPaletteFolder();
TFilePath getFxPresetFolder();
TFilePath getLibraryFolder();
TFilePath getReslistPath(bool forCleanup);
TFilePath getCacheRootFolder();
TFilePath getProfileFolder();
};

class FolderListenerManager {  // singleton

public:
  class Listener {
  public:
    virtual void onFolderChanged(const TFilePath &path) = 0;
    virtual ~Listener() {}
  };

private:
  std::set<Listener *> m_listeners;

  FolderListenerManager();

public:
  static FolderListenerManager *instance();

  ~FolderListenerManager();

  void notifyFolderChanged(const TFilePath &path);

  void addListener(Listener *listener);
  void removeListener(Listener *listener);
};

#endif
