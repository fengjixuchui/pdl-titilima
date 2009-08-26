/**
 * \file pdl_file.h
 * \brief PDL 文件操作相关类
 * \details 这个文件中定义了 PDL 中所有的文件操作类：
 *   \li \c LFile PDL 基本文件操作类
 *   \li \c LTxtFile PDL 文本文件操作类
*/

#pragma once

#include <pdl_base.h>

/**
 * \class LFile
 * \brief PDL 基本文件操作类
 * \details LFile 是 PDL 最基本文件操作封装，它封装了大部分常用的文件操作 API 函数。
 */
class LFile
{
public:
    LFile(void);
    ~LFile(void);
public:
    BOOL Close(void);
    BOOL Create(__in PCSTR lpFileName, __in DWORD dwDesiredAccess,
        __in DWORD dwShareMode, __in DWORD dwCreationDisposition,
        __in DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL);
    BOOL Create(__in PCWSTR lpFileName, __in DWORD dwDesiredAccess,
        __in DWORD dwShareMode, __in DWORD dwCreationDisposition,
        __in DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL);

    /**
     * 判断给定的文件是否存在。
     * @param [in] lpszFileName 要判断的文件名。
     * @param [in] bIncludeDir 是否包含目录。
     * @return 如果文件存在则返回 TRUE，否则返回 FALSE。
     */
    static BOOL Exists(__in PCSTR lpszFileName, __in BOOL bIncludeDir = TRUE);

    /**
     * 判断给定的文件是否存在。
     * @param [in] lpszFileName 要判断的文件名。
     * @param [in] bIncludeDir 是否包含目录。
     * @return 如果文件存在则返回 TRUE，否则返回 FALSE。
     */
    static BOOL Exists(__in PCWSTR lpszFileName, __in BOOL bIncludeDir = TRUE);

    BOOL Flush(void);

    /**
     * 获取文件的句柄。
     * @return 文件对象对应的句柄。
     */
    HANDLE GetHandle(void) const;

    DWORD GetPointer(void);
    DWORD GetSize(void);

    /**
     * 匹配文件名。
     * @param [in] lpszFileName 要匹配的文件名。
     * @param [in] lpszMatch 要匹配的模式字符串。
     * @return 如果匹配成功则返回 TRUE，否则返回 FALSE。
     */
    static BOOL MatchName(__in PCSTR lpszFileName, __in PCSTR lpszMatch);

    /**
     * 匹配文件名。
     * @param [in] lpszFileName 要匹配的文件名。
     * @param [in] lpszMatch 要匹配的模式字符串。
     * @return 如果匹配成功则返回 TRUE，否则返回 FALSE。
     */
    static BOOL MatchName(__in PCWSTR lpszFileName, __in PCWSTR lpszMatch);

    DWORD Read(__out PVOID lpBuffer, __in DWORD dwSize);
    DWORD SetPointer(__in LONG lPointer, __in DWORD dwMoveMethod);
    DWORD Write(__in LPCVOID lpBuffer, __in DWORD dwSize);
protected:
    /**
     * 文件对象对应的句柄
     */
    HANDLE m_hFile;
};

/**
 * \class LTxtFile
 * \brief PDL 文本文件操作类
 * \details LTxtFile 是 PDL 对文本文件操作的封装类。
 */

class LStringA;
class LTxtFile : private LFile
{
public:
    LTxtFile(void);
    ~LTxtFile(void);
public:

    /**
     * 打开一个文件，并向文件中追加数据。
     * @param [in] lpFileName 要打开的文件名。
     * @return 如果打开成功则返回 TRUE，否则返回 FALSE。
     */
    BOOL Append(__in PCSTR lpFileName);

    /**
     * 打开一个文件，并向文件中追加数据。
     * @param [in] lpFileName 要打开的文件名。
     * @return 如果打开成功则返回 TRUE，否则返回 FALSE。
     */
    BOOL Append(__in PCWSTR lpFileName);

    BOOL Close(void);

    /**
     * 是否已达文件末尾。
     * @return 如果当前已经到达文件末尾则返回 TRUE，否则返回 FALSE。
     */
    BOOL Eof(void);

    BOOL Flush(void);

    /**
     * 以读写模式打开文件。
     * @param [in] lpFileName 要打开的文件名。
     * @return 如果打开成功则返回 TRUE，否则返回 FALSE。
     */
    BOOL Open(__in PCSTR lpFileName);

    /**
     * 以读写模式打开文件。
     * @param [in] lpFileName 要打开的文件名。
     * @return 如果打开成功则返回 TRUE，否则返回 FALSE。
     */
    BOOL Open(__in PCWSTR lpFileName);

    /**
     * 读取文本。
     * @param [out] str 读取数据输出的字符串。
     * @param [in] 要读取的字符数。
     * @return 如果成功则返回 TRUE，否则返回 FALSE。
     */
    BOOL Read(__out LStringA* str, __in DWORD dwSize);

    /**
     * 读取一行文本。
     * @param [out] str 读取数据输出的字符串。
     * @return 如果成功则返回 TRUE，否则返回 FALSE。
     */
    BOOL ReadLn(__out LStringA* str);

    /**
     * 打开一个文件，并将其内容清空。
     * @param [in] lpFileName 要打开的文件名。
     * @return 如果打开成功则返回 TRUE，否则返回 FALSE。
     */
    BOOL Reset(__in PCSTR lpFileName);

    /**
     * 打开一个文件，并将其内容清空。
     * @param [in] lpFileName 要打开的文件名。
     * @return 如果打开成功则返回 TRUE，否则返回 FALSE。
     */
    BOOL Reset(__in PCWSTR lpFileName);

    /**
     * 向文件中写入文本。
     * @param [in] str 要写入的字符串。
     * @return 如果写入成功则返回 TRUE，否则返回 FALSE。
     */
    BOOL Write(__in PCSTR str);

    /**
     * 向文件中写入一行文本。
     * @param [in] str 要写入的字符串。
     * @return 如果写入成功则返回 TRUE，否则返回 FALSE。
     */
    BOOL WriteLn(__in PCSTR str);

protected:
    /**
     * 将当前缓存中的数据复制到目标缓冲区。
     */
    DWORD CopyToBuffer(__out PSTR buf, __in DWORD dwCnt);
    /**
     * 查找当前缓存中换行符的位置。
     */
    int FindCRLF(void);
    /**
     * 读取缓存块。
     */
    DWORD ReadBlock(void);
    /**
     * 开始读操作。
     */
    void StartRead(void);
    /**
     * 开始写操作。
     */
    void StartWrite(void);
protected:
    /**
     * 文件操作标志
     */
    DWORD m_dwFlags;
    /**
     * 数据缓冲区
     */
    PSTR m_buf;
    /**
     * 当前缓冲区指针
     */
    DWORD m_ptr;
    /**
     * R - 可读数据的大小；W - 待写入的数据位置
     */
    DWORD m_rwptr;
};
