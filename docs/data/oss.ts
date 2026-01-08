export type OssProject = {
  draft?: boolean;
  name: string;
  tagline: string;
  role?: string;
  tags: string[];
  cover?: string;
  repo?: string;
  homepage?: string;
  doc?: string;
};

export type OssPullRequest = {
  draft?: boolean;
  title: string;
  repo: string;
  url: string;
  summary: string;
  tags: string[];
};

export const projects: OssProject[] = [
  {
    draft: false,
    name: "Sidebundle",
    tagline: "Linux软件安装包的生成器/镜像最小化工具",
    tags: ["Linux", "portable", "Docker"],
    cover: "../statics/sidebundle.svg",
    repo: "https://github.com/xiaoniaoyouhuajiang/sidebundle",
    homepage: "https://github.com/xiaoniaoyouhuajiang/sidebundle#",
  },
];

export const pullRequests: OssPullRequest[] = [
  {
    draft: true,
    title: "PR 标题（替换我）",
    repo: "org/repo",
    url: "https://github.com/org/repo/pull/123",
    summary:
      "用 1-2 句话写清楚：问题是什么，你做了什么，带来什么影响（替换我）",
    tags: ["Bugfix", "Docs", "CI"],
  },
];
