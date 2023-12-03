#pragma once

#include "NGS/base/base.h"
#include "NGS/extend/function.h"

NGS_BEGIN
class NGS_DLL_API  Event : public TypeDefined<Event> {
public:
	NGS_TYPE_DEFINE(nstring, string);
	NGS_TYPE_DEFINE(nstring_view, view);
	NGS_TYPE_DEFINE(void_ptr, target);
	/*union _type {
		__string string;
		__sign id;

		_type(__string_ref_cst str):
			string(str)
		{}
		_type(__sign id) :
			id(id)
		{}
		_type(const _type& other){
			MemoryCopy(this, &other, sizeof(_type));
		}
		~_type() noexcept {}

		_type& operator=(__string_ref_cst str) { string = str; }
		_type& operator=(__sign id) { this->id = id; }

		bool operator==(const _type& other) { return string == other.string || id == other.id; }
		bool operator==(__string_ref_cst str) { return string == str; }
		friend bool operator==(__string_ref_cst str,const _type& self) { return self == str; }
		bool operator==(__sign id) { return this->id == id; }
		friend bool operator==(__sign id, const _type& self) { return self == id; }

	};*/
	NGS_TYPE_DEFINE(__string, type);

public:
#if NGS_HAS_CPP20
	constexpr Event(__string_ref_cst type) :
		type(type)
	{}
	constexpr Event() :
		type("")
	{}
#else
	Event(__string_ref_cst type) :
		type(type)
	{}
	Event() :
		type("")
	{}
#endif

	template<class  T>
	T& CurrentTarget() { return *static_cast<T*>(currentTarget); }

	__type_cst type;
	__target target = nullptr;
	__target currentTarget = nullptr;
	void_ptr param = nullptr;
};

class NGS_DLL_API  EventQueue : public TypeDefined<EventQueue> {
public:
	friend class  EventDispatcher;

	NGS_TYPE_DEFINE(Event, evt);
	NGS_TYPE_DEFINE(size_t, size);
	NGS_TYPE_DEFINE(std::queue<__evt>, cache);

public:
	void Dispatch(__evt_ref event) {
		_queue.push(event);
	}
	__evt PopEvent() {
		auto e = _queue.front();
		_queue.pop();
		return e;

	}

	__size Length()const { return _queue.size(); }
private:
	__cache _queue;
};

struct NGS_DLL_API EventListener {
	NGS_TYPE_DEFINE(EventListener, this);
	NGS_TYPE_DEFINE(void_ptr, target);
	NGS_TYPE_DEFINE(Event, evt);
	using callback = void(__evt_ref);
	using callback_ptr = void(*)(__evt_ref);
	NGS_TYPE_DEFINE(std::function<callback>, handler);

	__target currentTarget = nullptr;
	__handler handler;
	int priority = 0;

	EventListener(__handler_ref_cst handler, __target target = nullptr, int priority = 0) :
		currentTarget(target),
		handler(handler),
		priority(priority)
	{}

	auto operator<=>(__this_ref_cst other)const {
		return priority - other.priority;
	}
	bool operator==(__this_ref_cst other)const {
		return handler == other.handler;
	}
};

class NGS_DLL_API  EventDispatcher : public TypeDefined<EventDispatcher> {
public:
	NGS_TYPE_DEFINE(nstring, string);
	NGS_TYPE_DEFINE(nstring_view, string_v);
	NGS_TYPE_DEFINE(Event, evt);
	NGS_TYPE_DEFINE(EventQueue, queue);

	using callback = void(__evt_ref);
	using callback_ptr = void(*)(__evt_ref);
	NGS_TYPE_DEFINE(std::function<callback>, handler);
	NGS_TYPE_DEFINE(EventListener, listener);
	NGS_TYPE_DEFINE(std::vector<__listener>, listeners);
	using ___cache = std::map<__string, __listeners>;
	NGS_TYPE_DEFINE(___cache, cache);

public:
	/**
	* @brief 使用 EventDispatcher 对象注册事件侦听器对象，以使侦听器能够接收事件通知。可以为特定类型的事件、阶段和优先级在显示列表中的所有节点上注册事件侦听器。
	*
	* @note 成功注册一个事件侦听器后，无法通过额外调用 addEventListener() 来更改其优先级。要更改侦听器的优先级，必须首先调用 removeListener()。然后，可以使用新的优先级再次注册该侦听器。
	* @note 请记住，注册该侦听器后，如果继续调用具有不同 type 或 useCapture 值的 addEventListener()，则会创建单独的侦听器注册。例如，如果首先注册 useCapture 设置为 true 的侦听器，则该侦听器只在捕获阶段进行侦听。
	* @note 如果使用同一个侦听器对象再次调用 addEventListener()，并将 useCapture 设置为 false，那么便会拥有两个单独的侦听器：一个在捕获阶段进行侦听，另一个在目标和冒泡阶段进行侦听。
	* @note 不能只为目标阶段或冒泡阶段注册事件侦听器。这些阶段在注册期间是成对出现的，因为冒泡阶段只适用于目标节点的祖代。
	* @note 如果不再需要某个事件侦听器，可调用 removeEventListener() 删除它，否则会产生内存问题。事件侦听器不会自动从内存中删除，因为只要调度对象存在，垃圾回收器就不会删除侦听器（除非 useWeakReference 参数设置为 true）。
	* @note 复制 EventDispatcher 实例时并不复制其中附加的事件侦听器。（如果新近创建的节点需要一个事件侦听器，必须在创建该节点后附加该侦听器。）但是，如果移动 EventDispatcher 实例，则其中附加的事件侦听器也会随之移动。
	* @note 如果在正在处理事件的节点上注册事件侦听器，则不会在当前阶段触发事件侦听器，但会在事件流的稍后阶段触发，如冒泡阶段。
	* @note 如果从正在处理事件的节点中删除事件侦听器，则该事件侦听器仍由当前操作触发。删除事件侦听器后，决不会再次调用该事件侦听器（除非再次注册以备将来处理）。
	*
	* @param type:String — 事件的类型。
	* @param listener:Function — 处理事件的侦听器函数。此函数必须接受 Event 对象作为其唯一的参数，并且不能返回任何结果，如示例所示：function(evt:Event):void
	* @param useCapture:Boolean (default = false) — 确定侦听器是运行于捕获阶段还是运行于目标和冒泡阶段。如果将 useCapture 设置为 true，则侦听器只在捕获阶段处理事件，而不在目标或冒泡阶段处理事件。如果 useCapture 为 false，则侦听器只在目标或冒泡阶段处理事件。要在所有三个阶段都侦听事件，请调用 addEventListener 两次：一次将 useCapture 设置为 true，一次将 useCapture 设置为 false。
	* @param priority:int (default = 0) — 事件侦听器的优先级。优先级由一个带符号的 32 位整数指定。数字越大，优先级越高。优先级为 n 的所有侦听器会在优先级为 n -1 的侦听器之前得到处理。如果两个或更多个侦听器共享相同的优先级，则按照它们的添加顺序进行处理。默认优先级为 0。
	*
	*/
	void AddEventListener(__string type, __listener_ref_cst listener) {
		auto& listeners = _cache[type];
		listeners.push_back(listener);
		std::sort(listeners.begin(), listeners.end(), std::greater<__listener>());
	}
	/**
	* @brief 将事件调度到事件流中。事件目标是对其调用 dispatchEvent() 方法的 EventDispatcher 对象。
	*
	* @param event:Event — 调度到事件流中的 Event 对象。如果正在重新调度事件，则会自动创建此事件的一个克隆。在调度了事件后，其 target 属性将无法更改，因此您必须创建此事件的一个新副本以能够重新调度。
	*
	* @return 如果成功调度了事件，则值为 true。值 false 表示失败或对事件调用了 preventDefault()。
	*/
	bool Dispatch(__evt_ref event) const {
		auto&& search = _cache.find(event.type);
		if (search == _cache.end())return false;
		auto& listeners = search->second;
		for (auto& listener : listeners) {
			event.currentTarget = listener.currentTarget;
			listener.handler(event);
		}


		return true;
	}
	bool Dispatch(__evt_ref_cst event) const {
		return Dispatch(const_cast<__evt_ref>(event));
	}
	void Dispatch(__queue_ref queue) const {
		while (queue.Length())
			Dispatch(queue.PopEvent());
	}
	/**
	* @brief 检查 EventDispatcher 对象是否为特定事件类型注册了任何侦听器。这样，您就可以确定 EventDispatcher 对象在事件流层次结构中的哪个位置改变了对事件类型的处理。要确定特定事件类型是否确实触发了事件侦听器，请使用 willTrigger()。
	* @brief hasEventListener() 与 willTrigger() 的区别是：hasEventListener() 只检查它所属的对象，而 willTrigger() 检查整个事件流以查找由 type 参数指定的事件。 \
	*
	* @param type:String — 事件的类型。
	*
	* @return 如果指定类型的侦听器已注册，则值为 true；否则，值为 false。
	*/
	bool HasEventListener(__string_ref_cst type)const {
		auto&& search = _cache.find(type);
		if (search == _cache.end())return false;
		return false;
	}
	/**
	* @brief 从 EventDispatcher 对象中删除侦听器。如果没有向 EventDispatcher 对象注册任何匹配的侦听器，则对此方法的调用没有任何效果。
	*
	* @param type:String — 事件的类型。
	* @param listener:Function — 要删除的侦听器对象。
	* @param useCapture:Boolean (default = false) — 指出是为捕获阶段还是为目标和冒泡阶段注册了侦听器。如果为捕获阶段以及目标和冒泡阶段注册了侦听器，则需要对 removeEventListener() 进行两次调用才能将这两个侦听器删除，一次调用将 useCapture() 设置为 true，另一次调用将 useCapture() 设置为 false。
	*
	*
	*/
	void RemoveEventListener(__string_ref_cst type, __handler_ref_cst listener, bool useCapture = false) {
		auto&& search = _cache.find(type);
		if (search == _cache.end())return;
		auto& listeners = search->second;
		size_t i = 0;
		for (; i < listeners.size(); i++)
			if (listeners[i].handler == listener)break;

		if (i >= listeners.size())return;
		listeners.erase(listeners.begin() + i);
	}
	bool WillTrigger(__string_ref_cst type) const;

private:
	__cache _cache;
};

NGS_END