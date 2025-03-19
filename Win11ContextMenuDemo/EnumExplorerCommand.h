/*
 * @Descripttion: 
 * @version: 
 * @Author: Abo
 * @Date: 2025-03-19 21:39:41
 * @LastEditors: Abo
 * @LastEditTime: 2025-03-19 23:43:08
 * @FilePath: \Win11ContextMenuDemo\Win11ContextMenuDemo\EnumExplorerCommand.h
 */
#pragma once
#include "pch.h"

namespace Win11ContextMenuDemo::ExplorerCommand
{
    // EnumExplorerCommand 是一个类，用于实现 IEnumExplorerCommand 接口，用于枚举 IExplorerCommand 对象。
    // EnumExplorerCommand is a class that implements the IEnumExplorerCommand interface for enumerating IExplorerCommand objects.
    class EnumExplorerCommand : public winrt::implements<EnumExplorerCommand, IEnumExplorerCommand>
    {
    public:
        // 构造函数，接收一个 IExplorerCommand 对象列表。
        // Constructor that takes a list of IExplorerCommand objects.
        EnumExplorerCommand(std::vector<winrt::com_ptr<IExplorerCommand>> commands);

        // Next 方法用于获取序列中的下一个命令。
        // The Next method is used to retrieve the next command in the sequence.
        IFACEMETHODIMP Next(ULONG celt, __out_ecount_part(celt, *pceltFetched) IExplorerCommand** apUICommand, __out_opt ULONG* pceltFetched);

        // Skip 方法用于跳过序列中的一定数量的命令。
        // The Skip method is used to skip a certain number of commands in the sequence.
        IFACEMETHODIMP Skip(ULONG celt);

        // Reset 方法重置枚举器到初始状态。
        // The Reset method resets the enumerator to its initial state.
        IFACEMETHODIMP Reset();

        // Clone 方法用于创建此枚举器的一个副本。
        // The Clone method is used to create a copy of this enumerator.
        IFACEMETHODIMP Clone(__deref_out IEnumExplorerCommand** ppenum);

    private:
        // 存储一系列的 IExplorerCommand 对象。
        // Stores a series of IExplorerCommand objects.
        std::vector<winrt::com_ptr<IExplorerCommand>> sub_commands;

        // 当前枚举器的索引。
        // The current index of the enumerator.
        size_t currentIndex = 0;
    };
}
