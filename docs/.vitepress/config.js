import { defineConfig } from "vitepress";
import { globSync } from "glob";
import path from "path";
import { fileURLToPath } from "url";

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const docsRoot = path.resolve(__dirname, "..");

const ignorePatterns = [
  "code_src/**/target/**",
  "code_src/**/node_modules/**",
  "pdf_notes/**",
  "*.drawio",
  "*.html",
  "envs/**",
  "*.png",
  "*.jpg",
  "*.svg",
  "node_modules/**",
  "学习任务.md",
  "next_video.md",
  "inspirations.md",
  "onetab",
];

const dirDisplayMap = {
  "C++的强大": "C++",
  机器学习应用与理论: "机器学习",
  深度学习落地的道与术: "深度学习",
  并行思维与编程: "并行计算",
  编程生产力之元工具: "编程工具",
  编译原理: "编译原理",
  存储系统: "存储系统",
  网络与通信原理: "网络通信",
  算法puzzles: "算法",
  Python源码解析与奇技淫巧: "Python源码",
  Python高性能编码: "Python高性能",
  数理逻辑: "数理逻辑",
  问题分析: "问题分析",
};

const ignorePrefixes = new Set([
  ".vitepress",
  "statics",
  "data",
  "开源",
  ...ignorePatterns
    .map((pattern) => pattern.split("/**")[0])
    .filter((prefix) => prefix && !prefix.includes("*")),
]);

const sortByName = (a, b) =>
  a.localeCompare(b, "zh-Hans-CN", { numeric: true, sensitivity: "base" });

export default defineConfig({
  title: "ClassNotebook",
  description: "我的学习知识库",
  cleanUrls: true,

  ignoreDeadLinks: true,

  markdown: {
    ignoreDeadLinks: true,
    html: true,
    config(md) {
      md.options.html = true;
      md.options.breaks = false;
      md.options.linkify = false;
    },
  },

  themeConfig: {
    siteTitle: "ClassNotebook",

    nav: [{ text: "首页", link: "/" }],

    sidebar: generateSidebar(),

    socialLinks: [
      {
        icon: "github",
        link: "https://github.com/xiaoniaoyouhuajiang/ClassNotebook",
      },
    ],

    footer: {
      message: "知识在于积累",
      copyright: "Copyright © 2024-present",
    },

    outline: {
      level: [2, 3],
      label: "目录",
    },
  },

  ignore: ignorePatterns,
});

function generateSidebar() {
  const items = [];

  const dirs = globSync("*/", { dot: true, cwd: docsRoot })
    .map((d) => normalizePath(d))
    .filter((d) => !isIgnoredPath(d))
    .sort(sortByName);

  for (const dir of dirs) {
    const displayName = dirDisplayMap[dir] || dir;
    const group = buildDirGroup(dir, displayName);
    if (group) {
      items.push(group);
    }
  }

  return items;
}

function normalizePath(value) {
  return value.replace(/\\/g, "/").replace(/\/$/, "");
}

function isIgnoredPath(relPath) {
  const normalized = normalizePath(relPath);
  if (!normalized) {
    return true;
  }

  const baseName = path.basename(normalized);
  if (baseName.startsWith(".")) {
    return true;
  }

  for (const prefix of ignorePrefixes) {
    if (normalized === prefix || normalized.startsWith(`${prefix}/`)) {
      return true;
    }
  }

  return false;
}

function pickIndexFile(files) {
  const fileMap = new Map();
  for (const file of files) {
    fileMap.set(path.basename(file).toLowerCase(), file);
  }

  return fileMap.get("index.md") || fileMap.get("readme.md") || null;
}

function toSidebarLink(filePath) {
  return `/${filePath.replace(/\.md$/, "")}`;
}

function collectDirItems(relDir) {
  const normalized = normalizePath(relDir);
  const mdFiles = globSync(`${normalized}/*.md`, {
    cwd: docsRoot,
    nodir: true,
  });
  const indexFile = pickIndexFile(mdFiles);
  const indexFileBase = indexFile
    ? path.basename(indexFile).toLowerCase()
    : null;

  const mdItems = mdFiles
    .filter((file) => file !== indexFile)
    .sort(sortByName)
    .map((file) => ({
      text: path.basename(file, ".md"),
      link: toSidebarLink(file),
    }));

  const subDirs = globSync(`${normalized}/*/`, {
    cwd: docsRoot,
    dot: true,
  })
    .map((dir) => normalizePath(dir))
    .filter((dir) => !isIgnoredPath(dir))
    .sort(sortByName);

  const subItems = [];
  for (const dir of subDirs) {
    const group = buildDirGroup(dir);
    if (group) {
      subItems.push(group);
    }
  }

  return {
    items: [...mdItems, ...subItems],
    link: indexFile
      ? indexFileBase === "index.md"
        ? `/${normalized}/`
        : toSidebarLink(indexFile)
      : undefined,
  };
}

function buildDirGroup(relDir, textOverride) {
  const { items, link } = collectDirItems(relDir);
  if (items.length === 0 && !link) {
    return null;
  }

  const group = {
    text: textOverride || path.basename(relDir),
    collapsed: true,
  };

  if (link) {
    group.link = link;
  }

  if (items.length > 0) {
    group.items = items;
  }

  return group;
}
