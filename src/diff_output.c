#include "buf_text.h"
		(git_off_t)((size_t)delta->new_file.size) != delta->new_file.size) {

	if (file->mode == GIT_FILEMODE_COMMIT) {
		(error = git_submodule_status(&sm_status, sm)) < 0) {

		/* GIT_EEXISTS means a "submodule" that has not been git added */
		if (error == GIT_EEXISTS)
			error = 0;
	}
			(sm_head = git_submodule_head_id(sm)) != NULL) {

static int get_filtered(
	git_map *map, git_file fd, git_diff_file *file, git_vector *filters)
{
	int error;
	git_buf raw = GIT_BUF_INIT, filtered = GIT_BUF_INIT;

	if ((error = git_futils_readbuffer_fd(&raw, fd, (size_t)file->size)) < 0)
		return error;

	if (!filters->length)
		git_buf_swap(&filtered, &raw);
	else
		error = git_filters_apply(&filtered, &raw, filters);

	if (!error) {
		map->len  = git_buf_len(&filtered);
		map->data = git_buf_detach(&filtered);

		file->flags |= GIT_DIFF_FLAG__FREE_DATA;
	}

	git_buf_free(&raw);
	git_buf_free(&filtered);

	return error;
}

		read_len = p_readlink(path.ptr, map->data, alloc_len);
		if (!file->size && !(file->size = git_futils_filesize(fd)))
			goto close_and_cleanup;
			if (!error)
				file->flags |= GIT_DIFF_FLAG__UNMAP_DATA;
		if (error != 0)
			error = get_filtered(map, fd, file, &filters);
		!git_oid__cmp(&delta->old_file.oid, &delta->new_file.oid)) {

		/* patch is diffable only for non-binary, modified files where at
		 * least one side has data and there is actual change in the data
		 */
			(patch->old_data.len != patch->new_data.len ||
			 !git_oid_equal(&delta->old_file.oid, &delta->new_file.oid)))
static int callback_error(void)
{
	giterr_clear();
	return GIT_EUSER;
}

		return callback_error();
	int abbrevlen;
	char start_oid[GIT_OID_HEXSZ+1], end_oid[GIT_OID_HEXSZ+1];
	if (git_repository__cvar(&abbrevlen, pi->diff->repo, GIT_CVAR_ABBREV) < 0)
		return -1;

	abbrevlen += 1; /* for NUL byte */
	if (abbrevlen < 2)
		abbrevlen = 2;
	else if (abbrevlen > (int)sizeof(start_oid))
		abbrevlen = (int)sizeof(start_oid);

	git_oid_tostr(start_oid, abbrevlen, &delta->old_file.oid);
	git_oid_tostr(end_oid, abbrevlen, &delta->new_file.oid);
	if (S_ISDIR(delta->new_file.mode) ||
		delta->status == GIT_DELTA_UNMODIFIED ||
		delta->status == GIT_DELTA_IGNORED ||
		(delta->status == GIT_DELTA_UNTRACKED &&
		 (pi->diff->opts.flags & GIT_DIFF_INCLUDE_UNTRACKED_CONTENT) == 0))
		return callback_error();
		return callback_error();
		return callback_error();
		return callback_error();
	if (git_oid__cmp(&delta->new_file.oid, &delta->old_file.oid) == 0)