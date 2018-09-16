package com.aliyun.tianchi.mgr.evaluate.evaluate.file.evaluator;


import java.util.List;
import java.util.ArrayList;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.InputStream;
import java.io.ByteArrayInputStream;
import java.io.BufferedReader;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.InputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;
import com.google.common.base.Charsets;
import org.apache.commons.lang3.tuple.Pair;
import org.apache.commons.lang3.tuple.ImmutablePair;

/**
 * Created by mou.sunm on 2018/08/19.
 */
public class AlibabaSchedulerEvaluatorRun {
    // 参数
    public static final double  beta              = 0.5;
    public static final int     T2                = 98 * 15;
    public static final int     EXEC_LIMIT        = 3;
    
    private List<Problem> problems; 
    
    // 评测问题
    protected double evaluate(BufferedReader bufferedReader) throws IOException {
        double costs = 0.;
        for (int iter = 0 ; iter < problems.size(); iter++) {
            System.out.print("正在评测第" + iter + "份数据, 得分：");
            double cost = problems.get(iter).evaluate(bufferedReader);
            costs += cost;
            System.out.println("" + cost);
        }
        return costs / problems.size();
    }
    
    // 读取数据
    protected void init(BufferedReader bufferedReader) throws IOException {
        problems = new ArrayList<Problem>();
        while (true) {
            String firstLine = bufferedReader.readLine();
            if (firstLine == null) break;
            System.out.print("正在读取第" + problems.size() + "份数据");
            Problem prob = new Problem();
            prob.init(firstLine, bufferedReader);
            problems.add(prob);
            System.out.println("，成功");
        }
    }
    
    // 主函数
    public static void main(String[] args) throws Exception {
        if (args.length != 6 && args.length != 2){
            System.err.println("传入参数有误，使用方式为：");
            System.err.println("\t\tjava -cp xxx.jar com.aliyun.tianchi.mgr.evaluate.evaluate.file.evaluator.AlibabaSchedulerEvaluatorRun app_resources.csv machine_resources.csv instance_deploy.csv app_interference.csv job_info.csv result.csv");
            System.err.println("或：");
            System.err.println("\t\tjava -cp xxx.jar com.aliyun.tianchi.mgr.evaluate.evaluate.file.evaluator.AlibabaSchedulerEvaluatorRun judge.csv result.csv");
            return;
        }
        
        InputStream problemIS;
        InputStream resultIS;
        if (args.length == 6) {
            // 将赛题拼成评测数据
            StringBuffer sb = new StringBuffer();
            for (int i = 0; i < 5; i++) {
                List<String> lines = new ArrayList<String>();
                BufferedReader bs = new BufferedReader(new FileReader(new File(args[i])));
                for (String line = bs.readLine(); line != null; line = bs.readLine())
                    lines.add(line);
                sb.append(""+lines.size());
                for (String line : lines)
                    sb.append("\n").append(line);
                if (i != 4) sb.append("\n");
            }
            String alldata = sb.toString();
            problemIS = new ByteArrayInputStream(alldata.getBytes());
            resultIS = new FileInputStream(args[5]);
        }
        else {
            problemIS = new FileInputStream(args[0]);
            resultIS = new FileInputStream(args[1]);
        }
        
        // 评测
        AlibabaSchedulerEvaluatorRun evaluator = new AlibabaSchedulerEvaluatorRun();
        evaluator.init(new BufferedReader(new InputStreamReader(problemIS, Charsets.UTF_8)));
        double score = evaluator.evaluate(new BufferedReader(new InputStreamReader(resultIS, Charsets.UTF_8)));
        System.out.println("选手所得分数为：" + score);
    }
    
    
    class Problem {
        // 静态数据
        private int                     n;                  // app数
        private int                     N;                  // inst数
        private int                     m;                  // machine数
        private int                     k = 2*T2 + 4;       // 资源种类
        private Map<String, Integer>    appIndex;
        private Map<String, Integer>    machineIndex;
        private String[]                apps;
        private String[]                machines;
        private Map<String, Integer>    inst2AppIndex;
        private double[][]              appResources;  
        private double[][]              machineResources;  
        private Map<Integer, Integer>[] appInterference;
        
        private String[]                jobs;
        private int                     jobN;
        private Map<String, Integer>    jobIndex;
        private double[][]              jobResources;
        private int[]                   jobR;
        private int[]                   jobV;
        private Set<Integer>[]          jobFa;

        // 动态数据
        private Map<String, Integer>       inst2Machine;
        private double[][]                 machineResourcesUsed;
        private Map<Integer, Integer>[]    machineHasApp;

        public void init(String firstLine, BufferedReader bufferedReader) throws IOException {
            /** Read app_resources */
            n = Integer.parseInt(firstLine);
            apps = new String[n];
            appIndex = new HashMap<String, Integer>();
            appResources = new double[n][k];
            for (int i = 0; i < n; i++) {
                // appId,resources
                String line = bufferedReader.readLine();
                String[] parts = line.split(",", -1);
                List<Double> resources = new ArrayList<Double>();
                for (String x : parts[1].split("\\|", -1)) {
                    double cpu = Double.parseDouble(x);
                    for (int tt = 0; tt < 15; tt++)
                        resources.add(cpu);
                }
                for (String x : parts[2].split("\\|", -1)) {
                    double mem = Double.parseDouble(x);
                    for (int tt = 0; tt < 15; tt++)
                        resources.add(mem);
                }
                for (int j = 3; j < parts.length; j++)
                    resources.add(Double.parseDouble(parts[j]));
                if (k != resources.size()) 
                    throw new IOException("[DEBUG 2]Invaild problem: " + k + ", " + resources.size());
                if (appIndex.containsKey(parts[0]))
                    throw new IOException("[DEBUG 3]Invaild problem");
                appIndex.put(parts[0], i);
                apps[i] = parts[0];
                for (int j = 0; j < k; j++)
                    appResources[i][j] = resources.get(j);
            }
            /** Read machine_resources*/
            m = Integer.parseInt(bufferedReader.readLine());
            machineResources = new double[m][k];
            machineResourcesUsed = new double[m][k];
            machineIndex = new HashMap<String, Integer>();
            machineHasApp = new Map[m];
            machines = new String[m];
            for (int i = 0; i < m; i++) {
                // machineId,resources
                String line = bufferedReader.readLine();
                String[] parts = line.split(",", -1);
                if (machineIndex.containsKey(parts[0]))
                    throw new IOException("[DEBUG 4]Invaild problem");
                machineIndex.put(parts[0], i);
                machines[i] = parts[0];
                machineHasApp[i] = new HashMap<Integer, Integer>();
                double cpu = Double.parseDouble(parts[1]);
                double mem = Double.parseDouble(parts[2]);
                for (int j = 0; j < T2; j++) {
                    machineResources[i][j]   = cpu;
                    machineResources[i][T2+j] = mem;
                }
                for (int j = 3; j < parts.length; j++)
                    machineResources[i][2*T2 + j - 3] = Double.parseDouble(parts[j]);
                for (int j = 0; j < k; j++)
                    machineResourcesUsed[i][j] = 0.;
            }
            /** Read instance_deploy */
            N = Integer.parseInt(bufferedReader.readLine());
            inst2AppIndex = new HashMap<String, Integer>();
            inst2Machine  = new HashMap<String, Integer>();
            for (int i = 0; i < N; i++) {
                String line = bufferedReader.readLine();
                String[] parts = line.split(",", -1);
                if (inst2AppIndex.containsKey(parts[0]))
                    throw new IOException("[DEBUG 5]Invaild problem");
                if (!appIndex.containsKey(parts[1]))
                    throw new IOException("[DEBUG 6]Invaild problem");
                inst2AppIndex.put(parts[0], appIndex.get(parts[1]));
                if (!"".equals(parts[2])) {
                    if (!machineIndex.containsKey(parts[2]))
                        throw new IOException("[DEBUG 7]Invaild problem");
                    toMachine(parts[0], machineIndex.get(parts[2]), false);
                }
            }
            /** Read app_interference */
            int icnt = Integer.parseInt(bufferedReader.readLine());
            appInterference = new Map[n];
            for (int i = 0; i < n; i++)
                appInterference[i] = new HashMap<Integer, Integer>();
            for (int i = 0; i < icnt; i++) {
                String line = bufferedReader.readLine();
                String[] parts = line.split(",", -1);
                if (!appIndex.containsKey(parts[0]) || !appIndex.containsKey(parts[1]))
                    throw new IOException("[DEBUG 8]Invaild problem");
                int app1 = appIndex.get(parts[0]);
                int app2 = appIndex.get(parts[1]);
                int limit = Integer.parseInt(parts[2]);
                Map<Integer, Integer> inter = appInterference[app1];
                if (inter.containsKey(app2))
                    throw new IOException("[DEBUG 9]Invaild problem");
                if (app1 == app2) limit += 1; //self-interference +1 here
                inter.put(app2, limit);
            }
            /** Read job_info */
            jobN = Integer.parseInt(bufferedReader.readLine());
            jobs = new String[jobN];
            jobIndex = new HashMap<String, Integer>();
            jobResources = new double[jobN][2];
            jobV = new int[jobN];
            jobR = new int[jobN];
            jobFa = new Set[jobN];
            Set<String>[] tFa = new Set[jobN];
            for (int i = 0; i < jobN; i++) {
                tFa[i] = new HashSet<String>();
                String line = bufferedReader.readLine();
                String[] parts = line.split(",", -1);
                if (jobIndex.containsKey(parts[0]))
                    throw new IOException("[DEBUG 10]Invaild problem");
                jobIndex.put(parts[0], i);
                jobs[i] = parts[0];
                jobResources[i][0] = Double.parseDouble(parts[1]);
                jobResources[i][1] = Double.parseDouble(parts[2]);
                jobV[i] = Integer.parseInt(parts[3]);
                jobR[i] = Integer.parseInt(parts[4]);
                if (jobV[i] <= 0 || jobR[i] <= 0)
                    throw new IOException("[DEBUG 10.1]Invaild problem");
                for (int it = 5; it < parts.length; it++)
                    tFa[i].add(parts[it]);
            }
            for (int i = 0; i < jobN; i++) {
                jobFa[i] = new HashSet<Integer>();
                for (String job : tFa[i]) {
                    if (!jobIndex.containsKey(job)) continue;
                    jobFa[i].add(jobIndex.get(job));
                }
            }
        }

        public double evaluate(BufferedReader bufferedReader) throws IOException 
        {
            double costs = 0.;
            try {
                /** 读取执行数据 */
                List<Pair<String, Integer>>[] execs = new List[EXEC_LIMIT + 1];
                for (int i = 1; i <= EXEC_LIMIT; i++)
                    execs[i] = new ArrayList<Pair<String, Integer>>();
                List<Pair<Integer, Integer>> jobExec = new ArrayList<Pair<Integer, Integer>>();
                List<Pair<Integer, Integer>> jobExecDetail = new ArrayList<Pair<Integer, Integer>>();
                boolean readFail = false;
                boolean jobExecStart = false;
                for (String line = bufferedReader.readLine(); line != null && !line.equals("#"); line = bufferedReader.readLine()) {
                    String[] pair = line.split(",", -1);
                    if ((pair.length != 3 && pair.length != 4) ||
                            (pair.length == 3 && jobExecStart)) 
                    {
                        System.out.println("Read failed: " + line);
                        readFail = true; 
                        continue;
                    }
                    if (pair.length == 3) {
                        int stage = Integer.parseInt(pair[0]);
                        if (stage < 1 || stage > EXEC_LIMIT ||
                                !inst2AppIndex.containsKey(pair[1]) ||
                                !machineIndex.containsKey(pair[2]))
                        {
                            System.out.println("" + (stage < 1) + ", " + (stage > EXEC_LIMIT) +
                                    ", " + (!inst2AppIndex.containsKey(pair[1])) +
                                    ", " + (!machineIndex.containsKey(pair[2])));
                            readFail = true; 
                            continue;
                        }
                        execs[stage].add(new ImmutablePair(pair[1], machineIndex.get(pair[2])));
                    }
                    else {
                        jobExecStart = true;
                        if (!jobIndex.containsKey(pair[0]) || !machineIndex.containsKey(pair[1])) {
                            System.out.println("" + (!jobIndex.containsKey(pair[0])) + ", " + (!machineIndex.containsKey(pair[1])));
                            readFail = true; 
                            continue;
                        }
                        jobExec.add(new ImmutablePair(jobIndex.get(pair[0]), machineIndex.get(pair[1])));
                        jobExecDetail.add(new ImmutablePair(Integer.parseInt(pair[2]), Integer.parseInt(pair[3])));
                    }
                }
                if (readFail)
                    throw new Exception("Invaild solution file");
                /** app exec */
                for (int stage = 1; stage <= EXEC_LIMIT; stage++) {
                    /** 记录pickFrom */
                    Map<String, Integer> pickFrom = new HashMap<String, Integer>();
                    for (Pair<String, Integer> exec : execs[stage]) {
                        String inst = exec.getLeft();
                        if (!inst2Machine.containsKey(inst)) continue;
                        int fromMachine = inst2Machine.get(inst);
                        if (pickFrom.containsKey(inst))
                            throw new Exception("duplicate instance: " + inst);
                        pickFrom.put(inst, fromMachine);
                    }
                    /** 执行 */
                    for (Pair<String, Integer> exec : execs[stage]) {
                        String  inst        = exec.getLeft();
                        Integer machineIt   = exec.getRight();
                        String msg = toMachine(inst, machineIt);
                        if (!msg.equals("success"))
                            throw new Exception("执行失败, inst: " + inst + ", stage: " + stage + ", msg: " + msg);
                    }
                    /** 清理 */
                    for (String inst : pickFrom.keySet()) {
                        int machineIt = pickFrom.get(inst);
                        pickInstance(inst, machineIt);
                    }
                }
                /** job exec */
                int[] jobAsigned = new int[jobN];
                int[] jobFirstStart = new int[jobN];
                int[] jobLastEnd = new int[jobN];
                Set<Integer> hasJob = new HashSet<Integer>();
                for (int i = 0; i < jobN; i++) {
                    jobAsigned[i] = 0;
                    jobFirstStart[i] = T2;
                    jobLastEnd[i] = -1;
                }
                for (int it = 0; it < jobExec.size(); it++) {
                    int job = jobExec.get(it).getLeft();
                    int machineIt = jobExec.get(it).getRight();
                    int start = jobExecDetail.get(it).getLeft();
                    int cnt = jobExecDetail.get(it).getRight();
                    int end = start + jobR[job] - 1;
                    if (end >= T2 || start < 0)
                        throw new Exception("job TLE, job:" + jobs[job] + ", start:" + start);
                    if (cnt <= 0)
                        throw new Exception("job assignment <= 0");
                    hasJob.add(machineIt);
                    jobAsigned[job] += cnt;
                    jobFirstStart[job] = Math.min(jobFirstStart[job], start);
                    jobLastEnd[job] = Math.max(jobLastEnd[job], end);
                    for (int i = start; i <= end; i++) {
                        machineResourcesUsed[machineIt][i] += jobResources[job][0];
                        machineResourcesUsed[machineIt][T2+i] += jobResources[job][1];
                    }
                }
                /** 计算终态得分 */
                // 检查inst是否全部放入machine
                for (String inst : inst2AppIndex.keySet())
                    if (!inst2Machine.containsKey(inst)) throw new Exception("instance未全部分配, " + inst);
                // 检查job是否全部放入machine
                for (int job = 0; job < jobN; job++)
                    if (jobAsigned[job] != jobV[job]) throw new Exception("job未全部分配, " + jobs[job]);
                // 检查job是否满足DAG
                for (int job = 0; job < jobN; job++)
                    for (Integer fa : jobFa[job])
                        if (jobFirstStart[job] <= jobLastEnd[fa]) 
                            throw new Exception("DAG broken: " + jobs[fa] + ":" + jobLastEnd[fa] + " -> " 
                                    + jobs[job] + ":" + jobFirstStart[job]);
                // 检查machine的终态
                for (int j = 0; j < m; j++) {
                    Map<Integer, Integer> hasApp = machineHasApp[j];
                    if (hasApp.size() == 0 && !hasJob.contains(j)) continue;
                    // 检查互斥条件
                    int appCnt = 0;
                    for (Integer conditionalApp : hasApp.keySet()) {
                        if (hasApp.get(conditionalApp) <= 0) throw new Exception("[DEBUG 1]Stupid Judger.");
                        appCnt += hasApp.get(conditionalApp);
                        for (Integer checkApp : appInterference[conditionalApp].keySet()) {
                            if (hasApp.containsKey(checkApp)) {
                                if (hasApp.get(checkApp) > appInterference[conditionalApp].get(checkApp))
                                    throw new Exception("终态存在干扰冲突");
                            }
                        }
                    }
                    // 检查资源限制
                    for (int i = 0; i < k; i++)
                        if (dcmp(machineResourcesUsed[j][i] - machineResources[j][i]) > 0)
                            throw new Exception("终态存在资源过载");
                    // 技术得分
                    for (int t = 0; t < T2; t++) {
                        double usage = machineResourcesUsed[j][t] / machineResources[j][t];
                        costs += 1. + (1.+appCnt)*(Math.exp(Math.max(0., usage - beta)) - 1.);
                    }
                }
                costs /= T2;
            } catch (Exception e) {
                System.out.println(e.getMessage());
                //e.printStackTrace();
                costs = 1e9;
            }

            return costs;
        }

        private String toMachine(String inst, int machineIt)
        {
            return toMachine(inst, machineIt, true);
        }
        private String toMachine(String inst, int machineIt, boolean doCheck)
        {
            int appIt       = inst2AppIndex.get(inst);
            Map<Integer, Integer> hasApp = machineHasApp[machineIt];
            if (doCheck) {
                // 检查互斥规则
                int nowHas = 0;
                if (hasApp.containsKey(appIt))
                    nowHas = hasApp.get(appIt);
                for (Integer conditionalApp : hasApp.keySet()) {
                    if (hasApp.get(conditionalApp) <= 0) continue;
                    if (!appInterference[conditionalApp].containsKey(appIt)) continue;
                    if (nowHas + 1 > appInterference[conditionalApp].get(appIt)) {
                        return "App Interference, inst: " + inst + ", "
                            + apps[conditionalApp] + " -> " + apps[appIt] + ", "
                            + (nowHas + 1) + " > " + appInterference[conditionalApp].get(appIt); 
                    }
                }
                for (Integer checkApp : hasApp.keySet()) {
                    if (!appInterference[appIt].containsKey(checkApp)) continue;
                    if (hasApp.get(checkApp) > appInterference[appIt].get(checkApp)) {
                        return "App Interference, inst: " + inst + ", "
                            + apps[appIt] + " -> " + apps[checkApp] + ", "
                            + (nowHas + 1) + " > " + appInterference[appIt].get(checkApp); 
                    }
                }
                // 检查资源限制
                for (int i = 0; i < k; i++)
                    if (dcmp(machineResourcesUsed[machineIt][i] + appResources[appIt][i] - machineResources[machineIt][i]) > 0) 
                        return "Resource Limit: inst: " + inst + ", " 
                            + "machine: " + machines[machineIt] + ", app: " + apps[appIt] + ", resIter: " + i + ", "
                            + machineResourcesUsed[machineIt][i] + " + " + appResources[appIt][i] + " > " + machineResources[machineIt][i];
            }
            // 将inst放入新的machine
            inst2Machine.put(inst, machineIt);
            if (!hasApp.containsKey(appIt))
                hasApp.put(appIt, 0);
            hasApp.put(appIt, hasApp.get(appIt) + 1);
            for (int i = 0; i < k; i++)
                machineResourcesUsed[machineIt][i] += appResources[appIt][i];

            return "success";
        }
        private void pickInstance(String inst, int fromMachine) throws Exception
        {
            int appIt       = inst2AppIndex.get(inst);
            // 更新machineHasApp
            Map<Integer, Integer> fromHasApp = machineHasApp[fromMachine];
            if (!fromHasApp.containsKey(appIt))
                throw new Exception("[DEBUG 12] Stupid judger");
            fromHasApp.put(appIt, fromHasApp.get(appIt) - 1);
            if (fromHasApp.get(appIt) <= 0)
                fromHasApp.remove(appIt);
            // 更新machineResourcesUsed
            for (int i = 0; i < k; i++)
                machineResourcesUsed[fromMachine][i] -= appResources[appIt][i];
        }

        private int dcmp(double x) {
            if (Math.abs(x) < 1e-9) return 0;
            return x < 0. ? -1 : 1;
        }
    }
}
