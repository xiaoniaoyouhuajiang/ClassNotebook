---
layout: page
title: 开源
---

<script setup>
import { projects, pullRequests } from "../data/oss";

const visibleProjects = projects.filter((item) => !item.draft);
const visiblePullRequests = pullRequests.filter((item) => !item.draft);

function repoSlug(url) {
  if (!url) return null;
  try {
    const parsed = new URL(url);
    if (parsed.hostname !== "github.com") return null;
    let pathname = parsed.pathname || "";
    while (pathname.startsWith("/")) pathname = pathname.slice(1);
    while (pathname.endsWith("/")) pathname = pathname.slice(0, -1);
    const parts = pathname.split("/");
    if (parts.length < 2) return null;
    let repo = parts[1];
    if (repo.toLowerCase().endsWith(".git")) repo = repo.slice(0, -4);
    return `${parts[0]}/${repo}`;
  } catch {
    return null;
  }
}

function starsBadgeUrl(repoUrl) {
  const slug = repoSlug(repoUrl);
  if (!slug) return null;
  return `https://img.shields.io/github/stars/${slug}?style=flat&label=stars&color=0f766e`;
}
</script>
## 个人项目

<div class="oss-grid">
  <div v-if="visibleProjects.length === 0" class="oss-card">
    <div class="oss-title">
      <div class="oss-title-name">尚未添加项目</div>
      <div class="oss-title-role">在 `docs/data/oss.ts` 填写 `projects`</div>
    </div>
    <p class="oss-desc">建议每个项目只保留“一句话价值 + 3-6 个标签 + 1-3 个链接”，够精炼也便于长期维护。</p>
  </div>
  <div v-for="project in visibleProjects" :key="project.name" class="oss-card">
    <div class="oss-body">
      <div class="oss-title">
        <div class="oss-title-name">{{ project.name }}</div>
        <div v-if="project.role" class="oss-title-role">{{ project.role }}</div>
      </div>
      <p class="oss-desc">{{ project.tagline }}</p>
      <ul class="oss-tags">
        <li v-for="tag in project.tags" :key="tag" class="oss-tag">{{ tag }}</li>
      </ul>
      <div class="oss-links">
        <a v-if="project.repo" class="oss-link" :href="project.repo" target="_blank" rel="noreferrer">仓库</a>
        <a v-if="project.homepage" class="oss-link" :href="project.homepage" target="_blank" rel="noreferrer">主页</a>
        <a v-if="project.doc" class="oss-link" :href="project.doc">原理</a>
      </div>
    </div>
    <div class="oss-aside">
      <img
        class="oss-cover"
        :src="project.cover || '/oss-default.svg'"
        :alt="`${project.name} cover`"
        loading="lazy"
      />
      <img
        v-if="starsBadgeUrl(project.repo)"
        class="oss-stars"
        :src="starsBadgeUrl(project.repo)"
        alt="GitHub stars"
        loading="lazy"
      />
    </div>
  </div>
</div>

## 精选 PR

<div class="oss-grid">
  <div v-if="visiblePullRequests.length === 0" class="oss-card">
    <div class="oss-title">
      <div class="oss-title-name">尚未添加 PR</div>
      <div class="oss-title-role">在 `docs/data/oss.ts` 填写 `pullRequests`</div>
    </div>
    <p class="oss-desc"></p>
  </div>
  <div v-for="pr in visiblePullRequests" :key="pr.url" class="oss-card">
    <div class="oss-title">
      <div class="oss-title-name">{{ pr.title }}</div>
      <div class="oss-title-role">{{ pr.repo }}</div>
    </div>
    <p class="oss-desc">{{ pr.summary }}</p>
    <ul class="oss-tags">
      <li v-for="tag in pr.tags" :key="tag" class="oss-tag">{{ tag }}</li>
    </ul>
    <div class="oss-links">
      <a class="oss-link" :href="pr.url" target="_blank" rel="noreferrer">查看 PR</a>
    </div>
  </div>
</div>

<details class="stats-details">
  <summary>模板字段（精简口径）</summary>
  <div class="stats-note">
    <p><code>projects</code>（个人项目）建议字段：</p>
    <ul>
      <li><code>name</code>：项目名</li>
      <li><code>tagline</code>：一句话价值（解决什么问题）</li>
      <li><code>role</code>：你在其中的角色（可选）</li>
      <li><code>tags</code>：技术栈 / 关键词（3-6 个）</li>
      <li><code>repo/homepage/doc</code>：仓库/主页/原理页链接（按需）</li>
    </ul>
    <p><code>pullRequests</code>（精选贡献）建议字段：</p>
    <ul>
      <li><code>title</code>：PR 标题</li>
      <li><code>repo</code>：<code>org/repo</code></li>
      <li><code>url</code>：PR 链接</li>
      <li><code>summary</code>：1-2 句话说明问题→方案→影响</li>
      <li><code>tags</code>：类别标签（Bugfix/Perf/Docs/CI 等）</li>
    </ul>
  </div>
</details>
