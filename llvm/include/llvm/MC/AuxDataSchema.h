//
// Created by 5c4lar on 4/9/24.
//

#ifndef LLVM_AUXDATASCHEMA_H
#define LLVM_AUXDATASCHEMA_H
#include <gtirb/gtirb.hpp>
#include <map>
#include <string>
#include <tuple>
#include <vector>

namespace auxdata
{
/// ElfDynamicEntry is a tuple of the form {Tag, Value}.
using ElfDynamicEntry = std::tuple<std::string, uint64_t>;

/// ElfSymbolInfo is a tuple of the form {Size, Type, Binding, Visibility, SectionIndex}.
using ElfSymbolInfo = std::tuple<uint64_t, std::string, std::string, std::string, uint64_t>;

/// ElfSymbolTabIdxInfo is a vector of tuples of the form {Name, Index}.
using ElfSymbolTabIdxInfo = std::vector<std::tuple<std::string, uint64_t>>;

/// PeDataDirectory is a tuple of the form {Type, Address, Size}.
using PeDataDirectory = std::tuple<std::string, uint64_t, uint64_t>;

/// PeDebugData is a tuple of the form {Type, Address, Size}.
using PeDebugData = std::tuple<std::string, uint64_t, uint64_t>;

/// PeExportEntry is a tuple of the form {Address, Ordinal, Name}.
using PeExportEntry = std::tuple<uint64_t, int64_t, std::string>;

/// PeImportEntry is a tuple of the form {Iat_address, Ordinal, Function, Library}.
using PeImportEntry = std::tuple<uint64_t, int64_t, std::string, std::string>;

/// PeResource is a tuple of the form {Header, Data Length, Data Pointer}.
using PeResource = std::tuple<std::vector<uint8_t>, gtirb::Offset, uint64_t>;

/// Relocation is a tuple of the form
/// {Address, Type, Name, Addend, SymbolIndex, SectionName, RelType}.
using Relocation =
    std::tuple<uint64_t, std::string, std::string, int64_t, uint64_t, std::string, std::string>;

/// SymbolicExpressionInfo is a tuple of the form {UUID, offset, size, type, variant}.
using SymbolicExpressionInfo = std::map<std::tuple<gtirb::UUID, uint64_t>, std::tuple<uint32_t, uint32_t>>;
} // namespace auxdata

/// \file AuxDataSchema.h
/// \ingroup AUXDATA_GROUP
/// \brief AuxData types used by ddisasm that are not sanctioned.
/// \see AUXDATA_GROUP

namespace gtirb
{
namespace schema
{
/// \brief Auxiliary data that maps code blocks to integers
/// representing strongly connected components in the
/// intra-procedural CFG. (The CFG without taking into account
/// call and return edges.)
struct Sccs
{
  static constexpr const char* Name = "SCCs";
  typedef std::map<gtirb::UUID, int64_t> Type;
};

/// \brief Auxiliary data describing a binary's relocation records.
struct Relocations
{
  static constexpr const char* Name = "relocations";
  typedef std::set<auxdata::Relocation> Type;
};

/// \brief Auxiliary data describing a binary's dynamic entries.
struct DynamicEntries
{
  static constexpr const char* Name = "dynamicEntries";
  typedef std::set<auxdata::ElfDynamicEntry> Type;
};

/// \brief Auxiliary data mapping a section index to a section UUID.
struct SectionIndex
{
  static constexpr const char* Name = "sectionIndex";
  typedef std::map<uint64_t, gtirb::UUID> Type;
};

/// \brief Auxiliary data that stores the version of ddisasm used to
// produce the GTIRB.
struct DdisasmVersion
{
  static constexpr const char* Name = "ddisasmVersion";
  typedef std::string Type;
};

/// \brief Auxiliary data mapping PE load configuration field names to number values.
struct PeLoadConfig
{
  static constexpr const char* Name = "peLoadConfig";
  typedef std::map<std::string, uint64_t> Type;
};

// \brief Auxiliary data for PE resources.
struct PeResources
{
  static constexpr const char* Name = "peResources";
  typedef std::vector<auxdata::PeResource> Type;
};

/// \brief Auxiliary data representing the data directory entries of a PE file.
struct PeDataDirectories
{
  static constexpr const char* Name = "peDataDirectories";
  typedef std::vector<auxdata::PeDataDirectory> Type;
};

/// \brief Auxiliary data listing of debug data boundaries in a PE image.
struct PeDebugData
{
  static constexpr const char* Name = "peDebugData";
  typedef std::vector<auxdata::PeDebugData> Type;
};

/// \brief Auxiliary data for Souffle fact files.
struct SouffleFacts
{
  static constexpr const char* Name = "souffleFacts";
  // Entries of the form {Name, {TypeSignature, CSV}}.
  typedef std::map<std::string, std::tuple<std::string, std::string>> Type;
};

/// \brief Auxiliary data for Souffle output files.
struct SouffleOutputs
{
  static constexpr const char* Name = "souffleOutputs";
  // Entries of the form {Name, {TypeSignature, CSV}}.
  typedef std::map<std::string, std::tuple<std::string, std::string>> Type;
};

/// \brief Auxiliary data for the list of possible entry points in a raw binary.
struct RawEntries
{
  static constexpr const char* Name = "rawEntries";
  typedef std::vector<uint64_t> Type;
};

/// \brief Auxiliary data describing architecture information
struct ArchInfo
{
  static constexpr const char* Name = "archInfo";
  typedef std::map<std::string, std::string> Type;
};

/// \brief Auxiliary data listing of bytes appended to the binary that
/// are not loaded to memory.
struct Overlay
{
  static constexpr const char* Name = "overlay";
  typedef std::vector<uint8_t> Type;
};

// 5c4lar
/// \brief Auxilary data recording symbolic expression types and variant
struct SymbolicExpressionInfo
{
  static constexpr const char* Name = "symbolicExpressionInfo";
  typedef auxdata::SymbolicExpressionInfo Type;
};

} // namespace schema
} // namespace gtirb

#endif // LLVM_AUXDATASCHEMA_H
