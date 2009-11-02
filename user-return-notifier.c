macro_line|#include &lt;linux/user-return-notifier.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/module.h&gt;
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|hlist_head
comma
id|return_notifier_list
)paren
suffix:semicolon
macro_line|#define URN_LIST_HEAD per_cpu(return_notifier_list, raw_smp_processor_id())
multiline_comment|/*&n; * Request a notification when the current cpu returns to userspace.  Must be&n; * called in atomic context.  The notifier will also be called in atomic&n; * context.&n; */
r_void
id|user_return_notifier_register
c_func
(paren
r_struct
id|user_return_notifier
op_star
id|urn
)paren
(brace
"&t;"
id|set_tsk_thread_flag
c_func
(paren
id|current
comma
id|TIF_USER_RETURN_NOTIFY
)paren
suffix:semicolon
"&t;"
id|hlist_add_head
c_func
(paren
op_amp
id|urn-&gt;link
comma
op_amp
id|URN_LIST_HEAD
)paren
suffix:semicolon
)brace
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|user_return_notifier_register
)paren
suffix:semicolon
multiline_comment|/*&n; * Removes a registered user return notifier.  Must be called from atomic&n; * context, and from the same cpu registration occured in.&n; */
r_void
id|user_return_notifier_unregister
c_func
(paren
r_struct
id|user_return_notifier
op_star
id|urn
)paren
(brace
"&t;"
id|hlist_del
c_func
(paren
op_amp
id|urn-&gt;link
)paren
suffix:semicolon
"&t;"
r_if
c_cond
(paren
id|hlist_empty
c_func
(paren
op_amp
id|URN_LIST_HEAD
)paren
)paren
"&t;&t;"
id|clear_tsk_thread_flag
c_func
(paren
id|current
comma
id|TIF_USER_RETURN_NOTIFY
)paren
suffix:semicolon
)brace
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|user_return_notifier_unregister
)paren
suffix:semicolon
multiline_comment|/* Calls registered user return notifiers */
r_void
id|fire_user_return_notifiers
c_func
(paren
)paren
(brace
"&t;"
r_struct
id|user_return_notifier
op_star
id|urn
suffix:semicolon
"&t;"
r_struct
id|hlist_node
op_star
id|tmp1
comma
op_star
id|tmp2
suffix:semicolon
"&t;"
r_struct
id|hlist_head
op_star
id|head
suffix:semicolon
"&t;"
id|head
op_assign
op_amp
id|get_cpu_var
c_func
(paren
id|return_notifier_list
)paren
suffix:semicolon
"&t;"
id|hlist_for_each_entry_safe
c_func
(paren
id|urn
comma
id|tmp1
comma
id|tmp2
comma
id|head
comma
id|link
)paren
"&t;&t;"
id|urn
op_member_access_from_pointer
id|on_user_return
c_func
(paren
id|urn
)paren
suffix:semicolon
"&t;"
id|put_cpu_var
c_func
(paren
id|return_notifier_list
)paren
suffix:semicolon
)brace
eof
