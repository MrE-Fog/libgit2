	git_buf buffer;
	cl_assert(git_oid_cmp(&expected_blob_oid, &entry->id) == 0);
	memset(&buffer, 0, sizeof(git_buf));
	cl_git_pass(git_message_prettify(&buffer, "Initial commit", 0));
		buffer.ptr,
	git_buf_free(&buffer);

static void assert_commit_tree_has_n_entries(git_commit *c, int count)
{
	git_tree *tree;
	cl_git_pass(git_commit_tree(&tree, c));
	cl_assert_equal_i(count, git_tree_entrycount(tree));
	git_tree_free(tree);
}

static void assert_commit_is_head_(git_commit *c, const char *file, int line)
{
	git_commit *head;
	cl_git_pass(git_revparse_single((git_object **)&head, repo, "HEAD"));
	clar__assert(git_oid_equal(git_commit_id(c), git_commit_id(head)), file, line, "Commit is not the HEAD", NULL, 1);
	git_commit_free(head);
}
#define assert_commit_is_head(C) assert_commit_is_head_((C),__FILE__,__LINE__)

void test_object_commit_commitstagedfile__amend_commit(void)
{
	git_index *index;
	git_oid old_oid, new_oid, tree_oid;
	git_commit *old_commit, *new_commit;
	git_tree *tree;

	/* make a commit */

	cl_git_mkfile("treebuilder/myfile", "This is a file\n");
	cl_git_pass(git_repository_index(&index, repo));
	cl_git_pass(git_index_add_bypath(index, "myfile"));
	cl_repo_commit_from_index(&old_oid, repo, NULL, 0, "first commit");

	cl_git_pass(git_commit_lookup(&old_commit, repo, &old_oid));

	cl_assert_equal_i(0, git_commit_parentcount(old_commit));
	assert_commit_tree_has_n_entries(old_commit, 1);
	assert_commit_is_head(old_commit);

	/* let's amend the message of the HEAD commit */

	cl_git_pass(git_commit_amend(
		&new_oid, old_commit, "HEAD", NULL, NULL, NULL, "Initial commit", NULL));

	cl_git_pass(git_commit_lookup(&new_commit, repo, &new_oid));

	cl_assert_equal_i(0, git_commit_parentcount(new_commit));
	assert_commit_tree_has_n_entries(new_commit, 1);
	assert_commit_is_head(new_commit);

	git_commit_free(old_commit);
	old_commit = new_commit;

	/* let's amend the tree of that last commit */

	cl_git_mkfile("treebuilder/anotherfile", "This is another file\n");
	cl_git_pass(git_index_add_bypath(index, "anotherfile"));
	cl_git_pass(git_index_write_tree(&tree_oid, index));
	cl_git_pass(git_tree_lookup(&tree, repo, &tree_oid));
	cl_assert_equal_i(2, git_tree_entrycount(tree));

	cl_git_pass(git_commit_amend(
		&new_oid, old_commit, "HEAD", NULL, NULL, NULL, "Initial commit", tree));
	git_tree_free(tree);

	cl_git_pass(git_commit_lookup(&new_commit, repo, &new_oid));

	cl_assert_equal_i(0, git_commit_parentcount(new_commit));
	assert_commit_tree_has_n_entries(new_commit, 2);
	assert_commit_is_head(new_commit);

	/* cleanup */

	git_commit_free(old_commit);
	git_commit_free(new_commit);
	git_index_free(index);
}